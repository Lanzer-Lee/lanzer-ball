#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"

#define SERVO_FLAG  '#'

void set_servo_angle(uint8_t servo_id,uint16_t servo_angle,uint16_t servo_time);
void lift_ball(void);
void drop_ball(void);

#endif
