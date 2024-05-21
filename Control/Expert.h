#ifndef __EXPERT_H
#define __EXPERT_H

#include "stm32f10x.h"
#include "pid.h"
#include "motor.h"

typedef void (*ExpertMotorCallback)(int8_t velocity);

typedef struct{
    __IO float SetPoint;
    __IO float ActualValue;
    __IO float Error;
    __IO float *pFeedbackValue;
    __IO int8_t ControlValue;
    __IO ExpertMotorCallback pMotorCallback;
    __IO uint8_t Mode;
    __IO uint8_t Enable;
}Expert_TypeDef;

extern Expert_TypeDef expert;

void Expert_Init(Expert_TypeDef *Expert);
void Expert_Set(Expert_TypeDef *Expert,float target,uint8_t mode);
void Expert_Enable(Expert_TypeDef *Expert);
void Expert_Disable(Expert_TypeDef *Expert);
void Expert_Display(Expert_TypeDef *Expert);
int8_t Expert_Update(Expert_TypeDef *Expert);
void Expert_Control(Expert_TypeDef *Expert);

#endif
