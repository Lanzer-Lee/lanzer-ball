#ifndef __CONTROL_H
#define __CONTROL_H

#include "openmv.h"
#include "motor.h"

#define NOTMID  0
#define MID     1
#define INCR_LOCT_SELECT    1

#if INCR_LOCT_SELECT
/*increment PID*/
#define KP  8.50f
#define KI  5.00f
#define KD  0.10f
#define SMAPLSE_PID_SPEED   50
#else
/*position PID*/
#define KP  10.0f
#define KI  6.00f
#define KD  0.50f
#define SMAPLSE_PID_SPEED   50
#endif

typedef struct {
    __IO float SetPoint;
    __IO float ActualValue;
    __IO float SumError;
    __IO float Proportion;
    __IO float Integral;
    __IO float Derivative;
    __IO float Error;
    __IO float LastError;
    __IO float PrevError;
}PID_TypeDef;

extern PID_TypeDef g_speed_pid;

void pid_init(void);
int16_t increment_pid_control(PID_TypeDef *PID,float feedback_value);
int16_t position_pid_control(PID_TypeDef *PID,float feedback_value);

#endif
