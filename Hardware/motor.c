#include "motor.h"

uint8_t voltage[3]={0};
uint32_t encoder_total[MOTOR_NUM]={0};
int8_t velocity[MOTOR_NUM]={0};

void motor_init(void){
    uint8_t motor_type=MOTOR_TYPE_JGB37;
    uint8_t motor_encoder_polarity=0x01;
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_TYPE_JGB37,&motor_type,1);
    Delay_ms(5);
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_ENCODER_POLARITY_ADDR,&motor_encoder_polarity,1);
}

uint16_t read_voltage(void){
    IIC_Read_Bytes(CAM_I2C_ADDRESS,ADC_BAT_ADDR,voltage,2);
    return voltage[0]+(voltage[1]<<8);
}

void read_velocity(void){
    IIC_Read_Bytes(CAM_I2C_ADDRESS,MOTOR_ENCODER_TOTAL_ADDR,(uint8_t*)encoder_total,16);
}

void set_velocity(int8_t left_forward,int8_t right_forward,int8_t left_back,int8_t right_back){
    velocity[0]=left_forward;
    velocity[1]=right_forward;
    velocity[2]=left_back;
    velocity[3]=right_back;
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_FIXED_SPEED_ADDR,(uint8_t*)velocity,4);
}

void set_velocity_auto(void){
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_FIXED_SPEED_ADDR,(uint8_t*)velocity,4);
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
