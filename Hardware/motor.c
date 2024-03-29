#include "motor.h"

uint8_t voltage[3]={0};
int32_t encoder_total[MOTOR_NUM]={0};
uint8_t encoder_total_receive[MOTOR_NUM*4]={0};
int8_t velocity[MOTOR_NUM]={0};
int8_t brake_cmd[MOTOR_NUM]={0};

void motor_init(void){
    int8_t motor_type=MOTOR_TYPE_JGB37;
    int8_t motor_encoder_polarity=0;
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_TYPE_JGB37,&motor_type,4);
    Delay_ms(5);
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_ENCODER_POLARITY_ADDR,&motor_encoder_polarity,1);
    Delay_ms(5);
}

uint16_t read_voltage(void){
    IIC_Read_Bytes(CAM_I2C_ADDRESS,ADC_BAT_ADDR,voltage,2);
    return voltage[0]+(voltage[1]<<8);
}

void read_mileage(void){
    IIC_Read_Bytes_Encoder(CAM_I2C_ADDRESS,MOTOR_ENCODER_TOTAL_ADDR,encoder_total_receive,16);
}

void set_velocity(int8_t left_forward,int8_t right_forward,int8_t left_back,int8_t right_back){
    velocity[0]=left_forward;
    velocity[1]=right_forward;
    velocity[2]=left_back;
    velocity[3]=right_back;
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_FIXED_SPEED_ADDR,velocity,4);
}

void set_velocity_auto(void){
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_FIXED_SPEED_ADDR,velocity,4);
}

void standard_forward(int8_t motor_velocity){
    set_velocity(motor_velocity,motor_velocity,motor_velocity,motor_velocity);
}

void standard_backward(int8_t motor_velocity){
    set_velocity(-motor_velocity,-motor_velocity,-motor_velocity,-motor_velocity);
}

void standard_left(int8_t motor_velocity){
    set_velocity(motor_velocity,-motor_velocity,-motor_velocity,motor_velocity);
}

void standard_right(int8_t motor_velocity){
    set_velocity(-motor_velocity,motor_velocity,motor_velocity,-motor_velocity);
}

void standard_stop(void){
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_FIXED_SPEED_ADDR,brake_cmd,4);
}

void motor_data_process(void){
    uint8_t i=0;
    for(i=0;i<4;i++){
        velocity[i]=(Serial_RxPacket[4*i+2]-'0')*100+(Serial_RxPacket[4*i+3]-'0')*10+Serial_RxPacket[4*i+4]-'0';
        if(Serial_RxPacket[4*i+1]=='1')
        velocity[i]=-velocity[i];
    }
}

void encoder_data_process(void){
    uint8_t i=0;
    for(i=0;i<4;i++){
        encoder_total[i]=encoder_total_receive[4*i]<<24+encoder_total_receive[4*i+1]<<16+encoder_total_receive[4*i+2]<<8+encoder_total_receive[4*i+3];
    }
}
