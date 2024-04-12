#Dedicated to best zar
import sensor, image, time, os, tf, math, uos, gc
from machine import I2C
from vl53l1x import VL53L1X
from pyb import UART

#init sensor
sensor.reset()                         # Reset and initialize the sensor.
sensor.set_pixformat(sensor.RGB565)    # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)      # Set frame size to QVGA (320x240)
sensor.set_windowing((120, 120))       # Set 240x240 window.
sensor.skip_frames(time=2000)          # Let the camera adjust.
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

#init mark bucket
net = None
labels = None
min_confidence = 0.5

try:
# load the model, alloc the model file on the heap if we have at least 64K free after loading
    net = tf.load("trained.tflite", load_to_fb=uos.stat('trained.tflite')[6] > (gc.mem_free() - (64*1024)))
except Exception as e:
    raise Exception('Failed to load "trained.tflite", did you copy the .tflite and labels.txt file onto the mass-storage device? (' + str(e) + ')')
try:
    labels = [line.rstrip('\n') for line in open("labels.txt")]
except Exception as e:
    raise Exception('Failed to load "labels.txt", did you copy the .tflite and labels.txt file onto the mass-storage device? (' + str(e) + ')')

colors = [ # Add more colors if you are detecting more than 7 types of classes at once.
    (255,   0,   0),
    (  0, 255,   0),
    (255, 255,   0),
    (  0,   0, 255),
    (255,   0, 255),
    (  0, 255, 255),
    (255, 255, 255),
]

#init color
target_color_threshold = (23, 28, 14, 28, 9, 16)
brown_threshold = (9, 90, -33, 49, 9, 80)
white_thresholds = [(100, 84, -13, 7, -9, 8)]  # 白色的颜色阈值

#init uart
uart = UART(1, 115200)

#init laser and IIC
i2c = I2C(2)
distance = VL53L1X(i2c)

#init clock
clock = time.clock()
last_direction_time = time.ticks_ms()
stage_start_time = 0

#state machine
state=3
def next_state():
    '''
    state 0: only laser ranging
    state 1: find ball
    state 2: find mark bucket
    state 3: find white line based on zar correction
    state 4: find mark bucket use color green
    '''
    if uart.any():
        receive = uart.readline().decode()
        global state
        if(receive=="0"):
            state=0
        elif(receive=="1"):
            state=1
        elif(receive=="2"):
            state=2
        elif(receive=="3"):
            state=3
        elif(receive=="4"):
            state=4

#debug
def probe(x,y):
    if(state==0):
        print("({},{})".format(1,distance.read()))
    elif(state>0):
        print("({},{},{},{})".format(3,x,y,distance.read()))

def point_distance(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

#loop
while(True):
    clock.tick()
    img = sensor.snapshot().gamma_corr(gamma = 0.5, contrast = 1.0, brightness = 0.0)

    #only laser ranging
    if(state==0):
        if time.ticks_diff(time.ticks_ms(), last_direction_time) >= 300:
            uart.write("({},{})".format(1,distance.read()))
            uart.write("({},{},{},{})".format(3,-1,-1,distance.read()))
            probe(-1,-1)
            last_direction_time = time.ticks_ms()  # 更新最后一次输出方向的时间
            last_direction_time = time.ticks_ms()
        next_state()

    #find ball
    elif(state==1):
        ball_info=img.find_circles(threshold = 3500, x_margin = 10, y_margin = 10, r_margin = 10,r_min = 2, r_max = 100, r_step = 2)
        if(ball_info):
            for c in ball_info:
                area = (c.x()-c.r(), c.y()-c.r(), 2*c.r(), 2*c.r()) # 圆的外接矩形框
                img.draw_rectangle(area, color = (0, 255, 255))
                brown_blobs = img.find_blobs([brown_threshold], pixels_threshold=200, area_threshold=200, merge=True, roi=area)
                if brown_blobs:
                    # 计算棕色斑点总数
                    brown_pixels = sum(b[4] for b in brown_blobs)
                    # 计算圆内斑点总数
                    total_pixels = sum(b[4] for b in img.find_blobs([(0, 0, 0, 320, 240, 0)], pixels_threshold=1, area_threshold=1, merge=True, roi=area))
                    # 判断棕色斑点总数是否占圆内斑点总数的一半以上
                    if brown_pixels >= total_pixels / 4:
                        stage_start_time = time.ticks_ms()
                        b = brown_blobs[0]
                        img.draw_rectangle(b[0:4]) # rect
                        img.draw_cross(b[5], b[6]) # cx, cy
                        #Lm = (b[2]+b[3])/2
                        #length = K/Lm
                        if time.ticks_diff(time.ticks_ms(), last_direction_time) >= 10:
                            uart.write("({},{},{},{})".format(3,int(c.x()),int(c.y()),distance.read()))
                            probe(int(c.x()),int(c.y()))
                            last_direction_time = time.ticks_ms()  # 更新最后一次输出方向的时间
                            last_direction_time = time.ticks_ms()
        else:
            if time.ticks_diff(time.ticks_ms(), last_direction_time) >= 800:
                uart.write("({},{},{},{})".format(3,-1,-1,distance.read()))
                probe(-1,-1)
                last_direction_time = time.ticks_ms()  # 更新最后一次输出方向的时间
                last_direction_time = time.ticks_ms()
        next_state()

    #find mark bucket
    elif(state==2):
        bucket_info=net.detect(img, thresholds=[(math.ceil(min_confidence * 255), 255)])
        if(bucket_info[1]):
            for i, detection_list in enumerate(bucket_info):
                if (i == 0): continue # background class
                if (len(detection_list) == 0): continue # no detections for this class?
                for d in detection_list:
                    [x, y, w, h] = d.rect()
                    center_x = math.floor(x + (w / 2.0))
                    center_y = math.floor(y + (h / 2.0))
                    img.draw_circle((center_x, center_y, 12), color=colors[i], thickness=2)
                    if time.ticks_diff(time.ticks_ms(), last_direction_time) >= 50:
                        uart.write("({},{},{},{})".format(3,center_x,center_y,distance.read()))
                        probe(center_x,center_y)
                        last_direction_time = time.ticks_ms()
                        last_direction_time = time.ticks_ms()
                    continue
        else:
            if time.ticks_diff(time.ticks_ms(), last_direction_time) >= 400:
                uart.write("({},{},{},{})".format(3,-1,-1,distance.read()))
                probe(-1,-1)
                last_direction_time = time.ticks_ms()
                last_direction_time = time.ticks_ms()
        next_state()

    #find white line based on zar correction
    elif(state==3):
        #img = sensor.snapshot().gamma_corr(gamma = 0.5, contrast = 1.0, brightness = 0.0)
        blobs = img.find_blobs(white_thresholds)  # 查找满足颜色阈值的区域
        if blobs and len(blobs) <= 3:  # 当白色色块数量少于等于3时
            blobs.sort(key=lambda b: b.pixels(), reverse=True)  #排序
            rects = [b.rect() for b in blobs]   # 获取最大的白色色块的外接矩形
            best_matches = []   # 初始化最佳匹配平行四边形
            for rect in rects:
                best_matches.append([(rect[0], rect[1]),
                                     (rect[0] + rect[2], rect[1]),
                                     (rect[0] + rect[2], rect[1] + rect[3]),
                                     (rect[0], rect[1] + rect[3])])
            max_distance = 0        # 计算最类似平行四边形的相距最远的两个点
            max_points = None
            for i in range(len(best_matches)):
                for j in range(i+1, len(best_matches)):
                    for p1 in best_matches[i]:
                        for p2 in best_matches[j]:
                            d = point_distance(p1, p2)
                            if d > max_distance:
                                max_distance = d
                                max_points = (p1, p2)
            if max_points:
                x1, y1 = max_points[0]
                x2, y2 = max_points[1]
                if x1 > x2:
                    temp = x1
                    x1 = x2
                    x2 = temp
                    temp = y1
                    y1 = y2
                    y2 = temp
                slope = -math.atan2(y2 - y1, x2 - x1)  # 使用反正切函数计算斜率
                center = ((x1 + x2) / 2, (y1 + y2) / 2)
                if time.ticks_diff(time.ticks_ms(), last_direction_time) >= 50:
                    uart.write("({},{},{},{})".format(3, math.degrees(slope),center[1],distance.read()))
                    probe(math.degrees(slope),center[1])
                    last_direction_time = time.ticks_ms()
                    last_direction_time = time.ticks_ms()
                img.draw_circle(x1, y1, 5, color=(255, 0, 0))
                img.draw_circle(x2, y2, 5, color=(0, 0, 255))
                img.draw_line(int(x1), int(y1), int(x2), int(y2), color=(0, 255, 0))
    next_state()

    #find mark bucket based color
    elif(state==4):
        bucket_info=net.detect(img, thresholds=[(math.ceil(min_confidence * 255), 255)])
        if(bucket_info[1]):
            for i, detection_list in enumerate(net.detect(img, thresholds=[(math.ceil(min_confidence * 255), 255)])):
                if (i == 0): continue # background class
                if (len(detection_list) == 0): continue # no detections for this class?
                max_blob_area = 0
                max_blob = None
                for d in detection_list:
                    [x, y, w, h] = d.rect()
                    center_x = math.floor(x + (w / 2))
                    center_y = math.floor(y + (h / 2))
                    #print('(%d,%d)' % (center_x, center_y))
                    img.draw_circle((center_x, center_y, 12), color=colors[i], thickness=2)
                    # Search for green color within the detected object's bounding box
                    for pixel in img.find_blobs([(40, 100, -128, 127, -128, 127)], roi=(x, y, w, h)):
                        if pixel[4] > max_blob_area:
                            max_blob_area = pixel[4]
                            max_blob = pixel
                if max_blob:
                    img.draw_rectangle(max_blob[0:4], color=(0, 255, 0))
                    max_blob_center_x = max_blob[0] + max_blob[2] // 2
                    max_blob_center_y = max_blob[1] + max_blob[3] // 2
                    if time.ticks_diff(time.ticks_ms(), last_direction_time) >= 50:
                        uart.write("({},{},{},{})".format(3,max_blob_center_x, max_blob_center_y,distance.read()))
                        probe(max_blob_center_x, max_blob_center_y)
                        last_direction_time = time.ticks_ms()
                        last_direction_time = time.ticks_ms()
                        #print("Max Blob Center: (%d,%d,%d)" % (max_blob_center_x, max_blob_center_y,distance.read()))
        else:
            if time.ticks_diff(time.ticks_ms(), last_direction_time) >= 800:
                uart.write("({},{},{},{})".format(3,-1,-1,distance.read()))
                probe(-1,-1)
                last_direction_time = time.ticks_ms()
                last_direction_time = time.ticks_ms()
        next_state()

