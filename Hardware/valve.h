#ifndef __VALVE_H
#define __VALVE_H

#include "stm32f10x.h" 
#include "Delay.h"
#include "Serial.h"

extern uint16_t hit_time;

void valve_init(void);
void hit_ball(uint16_t time);
void valve_data_process(void);

#endif
