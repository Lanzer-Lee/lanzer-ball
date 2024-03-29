#ifndef __MOTOR_H
#define __MOTOR_H

#include "IIC.h"
#include "Serial.h"

#define CAM_I2C_ADDRESS             0x34
#define MOTOR_TYPE_ADDR             20
#define MOTOR_FIXED_SPEED_ADDR      51
#define MOTOR_ENCODER_POLARITY_ADDR 21
#define MOTOR_FIXED_PWM_ADDR        31
#define MOTOR_ENCODER_TOTAL_ADDR    60
#define ADC_BAT_ADDR                0
#define MOTOR_TYPE_WITHOUT_ENCODER  0
#define MOTOR_TYPE_TT               1
#define MOTOR_TYPE_N20              2
#define MOTOR_TYPE_JGB37            3
#define MOTOR_NUM                   4
#define BRAKE   '*'

extern uint8_t voltage[];
extern int32_t encoder_total[];
extern uint8_t encoder_total_receive[];
extern int8_t velocity[];
extern int8_t brake_cmd[];

void motor_init(void);
uint16_t read_voltage(void);
void read_mileage(void);
void set_velocity(int8_t left_forward,int8_t right_forward,int8_t left_back,int8_t right_back);
void set_velocity_auto(void);
void standard_forward(int8_t motor_velocity);
void standard_backward(int8_t motor_velocity);
void standard_left(int8_t motor_velocity);
void standard_right(int8_t motor_velocity);
void standard_stop(void);
void motor_data_process(void);
void encoder_data_process(void);

#endif
