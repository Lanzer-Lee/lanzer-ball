#ifndef __OPENMV_H
#define __OPENMV_H

#include "stm32f10x.h"
#include "Serial.h"
#include <stdio.h>
#include "motor.h"
#include "pid.h"
#include "Expert.h"

#define OPENMV_NULL   0
#define OPENMV_BASKETBALL   0
#define OPENMV_VOLLEYBALL   1
#define OPENMV_BUCKET   3
#define OPENMV_LINE   2
#define OPENMV_SEARCH_RIGHT 1
#define OPENMV_SEARCH_LEFT  0
#define OPENMV_SEARCH_SPEED 10
#define OPENMV_SCREEN_MID   80

typedef struct{
    __IO float X;
    __IO float Y;
    __IO float Distance;
    __IO float Slope;
    __IO uint8_t State;
    __IO uint8_t Flag;
    char Command[3];
}Openmv_TypeDef;

extern Openmv_TypeDef cv;

void openmv_init(Openmv_TypeDef *CV);
void openmv_set(Openmv_TypeDef *CV,uint8_t state);
void openmv_analysis(Openmv_TypeDef *CV);
uint8_t openmv_find_ball(Openmv_TypeDef *CV,uint8_t search_direction);
void openmv_aim_ball(Openmv_TypeDef *CV,uint8_t search_direction);
void openmv_reset(Openmv_TypeDef *CV);
void openmv_assert(Openmv_TypeDef *CV);

#endif
