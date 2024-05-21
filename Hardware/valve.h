#ifndef __VALVE_H
#define __VALVE_H

#include "stm32f10x.h"
#include "Delay.h"

#define VALVE_TIME  300

void valve_init(void);
void valve_hit(uint16_t time);

#endif
