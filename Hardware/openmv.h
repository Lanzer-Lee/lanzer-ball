#ifndef __OPENMV_H
#define __OPENMV_H

#include "stm32f10x.h"
#include "Serial.h"
#include <stdio.h>

#define STATE_LASER   0
#define STATE_BALL    1
#define STATE_BUCKET  2

typedef struct{
    __IO float x;
    __IO float y;
    __IO float distance;
}Openmv_TypeDef;

extern Openmv_TypeDef openmv;

void openmv_analysis(void);
void openmv_state_transfer(uint8_t state);
void laser_distance_control(float set_distance);
void find_ball(float target_pixel,uint8_t direction);
void find_bucket(float target_pixel,uint8_t direction);

#endif
