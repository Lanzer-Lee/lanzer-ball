#ifndef __ECHO_H
#define __ECHO_H

#include "stm32f10x.h"
#include "Delay.h"
#include "GAME.h"

extern __IO float echo_diatance;

void echo_init(void);
float echo_measure_distance(void);
void echo_aim_ball(void);

#endif
