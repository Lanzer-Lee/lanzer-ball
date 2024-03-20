#ifndef __VALVE_H
#define __VALVE_H

#include "stm32f10x.h" 
#include "Delay.h"
#include "Serial.h"
#include <stdio.h>

char valve_cmd[];

void valve_init(void);
void hit_ball(uint16_t time);

#endif
