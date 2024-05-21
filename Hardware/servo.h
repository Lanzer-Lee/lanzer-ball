#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"
#include "Serial.h"
#include "Delay.h"

#define SERVO_NUM   0x02
#define SERVO_WRITE 0x01
#define SERVO_MOVE_TIME 1000
#define SERVO_UP_ANGLE  150
#define SERVO_DOWN_ANGLE    600
#define SERVO_ID    0x01
#define SERVO_VIEW_ANGLE    300

typedef struct{
    __IO uint8_t ID;
    __IO uint16_t Time;
    __IO uint16_t Angle;
    __IO uint8_t Command[3*SERVO_NUM+7];
}Servo_TypeDef;

extern Servo_TypeDef servo;

void servo_init(Servo_TypeDef *Servo);
void servo_control(Servo_TypeDef *Servo);
void servo_up(Servo_TypeDef *Servo);
void servo_down(Servo_TypeDef *Servo);
void servo_view_ball(Servo_TypeDef *Servo);

#endif
