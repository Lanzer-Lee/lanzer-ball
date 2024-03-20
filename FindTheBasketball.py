# FindTheBaketball - By: zar - Wed Mar 13 2024

import sensor, image, time
from pyb import UART

# 初始化串口通信
uart = UART(3, 115200)  # 设置UART3，波特率为115200

# 配置颜色追踪参数
target_color_threshold = (23, 28, 14, 28, 9, 16)
brown_threshold = (10, 35, 4, 32, -7, 25)

# 初始化摄像头
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

# 标志变量，用于表示是否进入测距阶段
next_stage = 0

# 记录上一次输出方向的时间
last_direction_time = time.ticks_ms()

# 记录进入当前阶段的时间
stage_start_time = 0

while True:
    img = sensor.snapshot()

    if next_stage == 0:  # 如果尚在寻找篮球

        # 查找颜色斑点
        blobs = img.find_blobs([brown_threshold], pixels_threshold=200, area_threshold=200, merge=True)

        if blobs:
            # 选择最大的斑点（假设最大的就是我们要找的区域）
            largest_blob = max(blobs, key=lambda b: b.pixels())

            # 计算该区域的中点
            x = largest_blob.rect()[0] + largest_blob.rect()[2] * 0.5
            y = largest_blob.rect()[1] + largest_blob.rect()[3] * 0.5

            # 输出机器人的横坐标
            if time.ticks_diff(time.ticks_ms(), last_direction_time) >= 2000:  # 每两秒输出一次
               uart.write("(-{})\n".format(int(x)))  # 输出 x 值
               # print(x)
               last_direction_time = time.ticks_ms()  # 更新最后一次输出方向的时间

            # 绘制该区域的矩形边框
            img.draw_rectangle(largest_blob.rect())
            img.draw_cross(largest_blob.cx(), largest_blob.cy())

            # 查找篮球
            for c in img.find_circles(threshold=3500, x_margin=10, y_margin=10, r_margin=10,
                                      r_min=2, r_max=100, r_step=2):
                area = (c.x()-c.r(), c.y()-c.r(), 2*c.r(), 2*c.r())  # 圆的外接矩形框
                img.draw_rectangle(area, color=(255, 255, 255))

                # 查找棕色斑点
                brown_blobs = img.find_blobs([brown_threshold], pixels_threshold=200, area_threshold=200, merge=True, roi=area)
                if brown_blobs:
                    # 计算棕色斑点总数
                    brown_pixels = sum(b[4] for b in brown_blobs)
                    # 计算圆内斑点总数
                    total_pixels = sum(b[4] for b in img.find_blobs([(0, 0, 0, 320, 240, 0)], pixels_threshold=1, area_threshold=1, merge=True, roi=area))
                    # 判断棕色斑点总数是否占圆内斑点总数的一半以上
                    if brown_pixels >= total_pixels / 4:
                        # uart.write("(0000)\n")  # 发送“0000”表示检测到篮球
                        # print("0000")
                        img.draw_circle(c.x(), c.y(), c.r(), color=(255, 0, 0))
                        next_stage = 1 # 进入让篮球在中间位置的阶段

    elif next_stage == 1:  # 进入让篮球在中间的阶段

        # 查找圆
        for c in img.find_circles(threshold = 3500, x_margin = 10, y_margin = 10, r_margin = 10,
                r_min = 2, r_max = 100, r_step = 2):
            area = (c.x()-c.r(), c.y()-c.r(), 2*c.r(), 2*c.r()) # 圆的外接矩形框
            img.draw_rectangle(area, color = (255, 255, 255))

            # 查找棕色斑点
            brown_blobs = img.find_blobs([brown_threshold], pixels_threshold=200, area_threshold=200, merge=True, roi=area)
            if brown_blobs:
                # 计算棕色斑点总数
                brown_pixels = sum(b[4] for b in brown_blobs)
                # 计算圆内斑点总数
                total_pixels = sum(b[4] for b in img.find_blobs([(0, 0, 0, 320, 240, 0)], pixels_threshold=1, area_threshold=1, merge=True, roi=area))
                # 判断棕色斑点总数是否占圆内斑点总数的一半以上
                if brown_pixels >= total_pixels / 4:
                    stage_start_time = time.ticks_ms()
                    if time.ticks_diff(time.ticks_ms(), last_direction_time) >= 2000:  # 每两秒输出一次
                        uart.write("(+{})\n".format(int(c.x())))  # 输出 c.x 值
                        # print(c.x(), next_stage)
                        last_direction_time = time.ticks_ms()  # 更新最后一次输出方向的时间
                    if (c.x() <= 90) and (c.x() >= 70):
                        next_stage == 2 # 进入测距阶段

        if time.ticks_diff(time.ticks_ms(), stage_start_time) >= 10000:  # 如果超过十秒仍未检测到篮球
            next_stage = 0
            continue  # 继续下一次循环

    elif next_stage == 2: # 进入测距阶段
        pass
