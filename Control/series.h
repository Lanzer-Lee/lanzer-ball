#ifndef __SERIES_H
#define __SERIES_H

#include "stm32f10x.h"
#include "stdio.h"
#include "attitude.h"
#include "GAME.h"
#include "motor.h"
#include "Delay.h"

#define MODE_STRAIGHT    0
#define MODE_HORIZONTAL  1
#define MODE_ROTE        2
#define MODE_LINE        3

typedef struct{
    __IO float SetPoint;
    __IO float Error;
    __IO float *pFeedbackValue;
    __IO uint8_t Speed;
    __IO uint8_t Mode;
}Series_TypeDef;

extern Series_TypeDef series;

void series_init(Series_TypeDef *Series);
void series_set(Series_TypeDef *Series,float target,uint8_t speed,uint8_t mode);
uint8_t series_move(float displacement,int8_t velocity,uint8_t mode);
void series_control(Series_TypeDef *Series);

#endif
