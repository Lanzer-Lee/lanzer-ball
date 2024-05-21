#ifndef __DEBUG_H
#define __DEBUG_H

#include "stm32f10x.h"
#include "Serial.h"
#include "stdio.h"
#include "GAME.h"
#include "motor.h"
#include "valve.h"
#include "TOF.h"
#include "openmv.h"
#include "servo.h"
#include "pid.h"
#include "IMU.h"
#include "echo.h"
#include "power.h"
#include "Fusion.h"

#define GAME_DEBUG  'G'
#define MOTOR_DENUG 'M'
#define ATTITUDE_DEBUG  'A'
#define SERIES_DEBUG    'C'
#define VALVE_DUBUG     'V'
#define TOF_DEBUG   'T'
#define OPENMV_DEBUG    'O'
#define SERVO_DEBUG 'S'
#define PID_DEBUG   'P'
#define IMU_DEBUG   'I'
#define ECHO_DEBUG  'E'
#define POWER_DEBUG 'Q'
#define FUSION_DEBUG    'F'

#define INTEGER_NUM 5
#define FLOAT_NUM   7

typedef struct{
    __IO char Identifier;
    __IO int Data_int[INTEGER_NUM];
    __IO float Data_float[FLOAT_NUM];
}Debug_TypeDef;

extern Debug_TypeDef data;

void debug_init(Debug_TypeDef *Data);
void debug_analysis(Debug_TypeDef *Data);

#endif
