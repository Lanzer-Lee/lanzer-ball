#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"
#include "motor.h"
#include <stdio.h>
#include "series.h"
#include "openmv.h"
#include "TOF.h"

#define KP_POSITION 1.0f
#define KI_POSITION 0.1f
#define KD_POSITION 0.1f

#define SPEED_UPPER_BOUND   20
#define SPEED_LOWER_BOUND   2

#define ANGLE_DEADLINE  2
#define ANGLE_INTERGRAL_BOUND   45

#define POSITION_DEADLINE   3
#define POSITION_INTERGRAL_BOUND    40

typedef void (*MotorCallback)(int8_t velocity);

typedef struct{
    __IO float SetPoint;
    __IO float ActualValue;
    __IO float SumError;
    __IO float Proportion;
    __IO float Integral;
    __IO float Derivative;
    __IO float Error;
    __IO float LastError;
    __IO float PrevError;
    __IO float ControlValue;
    __IO float *pFeedbackValue;
    __IO MotorCallback pMotorCallback;
    __IO uint8_t Mode;
    __IO uint8_t Enable;
}PID_TypeDef;

extern PID_TypeDef pid;

void pid_init(PID_TypeDef *PID);
void pid_set(PID_TypeDef *PID,float target,uint8_t mode);
void pid_set_parameter(PID_TypeDef *PID,float Kp,float Ki,float Kd);
void pid_enable(PID_TypeDef *PID);
void pid_disable(PID_TypeDef *PID);
float pid_update(PID_TypeDef *PID);
void pid_control(PID_TypeDef *PID);

#endif
