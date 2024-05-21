#ifndef __ATTITUDE_H
#define __ATTITUDE_H

#include "stm32f10x.h"
#include "motor.h"
#include "GAME.h"
#include <math.h>

#define ERROR_BOUND 20

typedef struct{
    __IO float pre_mileage[5];
    __IO float old_mileage[5];
    __IO float diff_mileage[5];
    __IO int32_t pre_encoder[5];
    __IO int32_t old_encoder[5];
    __IO int32_t diff_encoder[5];
    __IO float x;
    __IO float y;
    __IO float angle;
}Robot_TypeDef;

extern Robot_TypeDef robot;

void attitude_init(Robot_TypeDef *Robot);
void attitude_algorithm(Robot_TypeDef *Robot);

#endif
