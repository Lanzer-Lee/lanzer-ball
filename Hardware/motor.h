#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"
#include "IIC.h"
#include "attitude.h"
#include "power.h"
#include <stdlib.h>

#define CAM_I2C_ADDRESS             0x34
#define MOTOR_TYPE_ADDR             20
#define MOTOR_FIXED_SPEED_ADDR      51
#define MOTOR_ENCODER_POLARITY_ADDR 21
#define MOTOR_FIXED_PWM_ADDR        31
#define MOTOR_ENCODER_TOTAL_ADDR    60
#define ADC_BAT_ADDR                0
#define MOTOR_TYPE_JGB37            3
#define MOTOR_NUM                   4
#define MOTOR_ENCODER_ERROR 30

typedef struct{
    uint16_t Voltage;
    uint8_t VoltageBuffer[3];
    int32_t PrevEncoder[MOTOR_NUM];
    int32_t LastEncoder[MOTOR_NUM];
    int32_t Encoder[MOTOR_NUM];
    int8_t Velocity[MOTOR_NUM];
}Motor_TypeDef;

extern Motor_TypeDef motor;

void Motor_Init(Motor_TypeDef *Motor);
void Motor_ReadVoltage(Motor_TypeDef *Motor);
uint8_t Motor_ReadEncoderCorrection(Motor_TypeDef *Motor);
void Motor_ReadEncoder(Motor_TypeDef *Motor);
void Motor_Encoder_Revise(Motor_TypeDef *Motor);
void Motor_SetVelocity(Motor_TypeDef *Motor,int8_t V_lf,int8_t V_rf,int8_t V_lb,int8_t V_rb);
void Motor_Straight(int8_t velocity);
void Motor_Horizontal(int8_t velocity);
void Motor_Rote(int8_t velocity);
void Motor_Stop(Motor_TypeDef *Motor);

#endif
