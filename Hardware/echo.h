#ifndef __ECHO_H
#define __ECHO_H

#include "stm32f10x.h"  
#include "Delay.h"

extern float echo_distance;

void echo_init(void);
float measure_distance(void);

#endif
