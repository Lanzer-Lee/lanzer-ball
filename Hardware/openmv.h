#ifndef __OPENMV_H
#define __OPENMV_H

#include "stm32f10x.h"
#include "Serial.h"

extern int16_t target_x;

void openmv_data_process(void);

#endif
