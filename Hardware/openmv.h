#ifndef __OPENMV_H
#define __OPENMV_H

#include "stm32f10x.h"
#include "Serial.h"
#include <stdio.h>

typedef struct{
    __IO int x;
    __IO int y;
    __IO float distance;
}Openmv_TypeDef;

extern Openmv_TypeDef openmv;

void openmv_data_process(void);
void openmv_analysis(void);

#endif
