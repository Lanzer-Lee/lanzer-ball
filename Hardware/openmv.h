#ifndef __OPENMV_H
#define __OPENMV_H

#include "stm32f10x.h"
#include "Serial.h"

typedef struct{
    __IO int16_t target_x;
    __IO int16_t target_y;
    __IO float target_distance;
}Openmv_TypeDef;

extern Openmv_TypeDef openmv_structure;

void openmv_data_process(void);

#endif
