#ifndef __MOTOR_H
#define __MOTOR_H

#include "IIC.h"
#include "Serial.h"

#define CAM_I2C_ADDRESS             0x34
#define MOTOR_TYPE_ADDR             0x14
#define MOTOR_FIXED_SPEED_ADDR      0x33
#define MOTOR_ENCODER_POLARITY_ADDR 0x15
#define MOTOR_FIXED_PWM_ADDR        0x1F
#define MOTOR_ENCODER_TOTAL_ADDR    0x3C
#define ADC_BAT_ADDR                0x00
#define MOTOR_TYPE_WITHOUT_ENCODER  0x00
#define MOTOR_TYPE_TT               0x01
#define MOTOR_TYPE_N20              0x02
#define MOTOR_TYPE_JGB37            0x03
#define MOTOR_NUM                   4

extern uint8_t voltage[];
extern uint32_t encoder_total[];
extern int8_t velocity[];

void motor_init(void);
uint16_t read_voltage(void);
void read_velocity(void);
void set_velocity(int8_t left_forward,int8_t right_forward,int8_t left_back,int8_t right_back);
void set_velocity_auto(void);
void standard_forward(int8_t motor_velocity);
void standard_backward(int8_t motor_velocity);
void standard_left(int8_t motor_velocity);
void standard_right(int8_t motor_velocity);
void standard_stop(void);
void motor_data_process(void);

#endif
