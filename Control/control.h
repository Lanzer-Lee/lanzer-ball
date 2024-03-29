#ifndef __CONTROL_H
#define __CONTROL_H

#include "openmv.h"
#include "motor.h"

#define NOTMID  0
#define MID     1
#define INCR_LOCT_SELECT    1

#if INCR_LOCT_SELECT
/*increment PID*/
#define KP  0.18f
#define KI  0.00f
#define KD  0.08f
#define SMAPLSE_PID_SPEED   50
#else
/*position PID*/
#define KP  10.0f
#define KI  6.00f
#define KD  0.50f
#define SMAPLSE_PID_SPEED   50
#endif

#define SPEED_UPPER_BOUND   20
#define SPEED_LOWER_BOUND   -20

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
extern int16_t auto_velocity;
extern uint8_t PID_Status;

void pid_init(void);
void set_pid_target(float target);
int16_t increment_pid_control(PID_TypeDef *PID,float feedback_value);
int16_t position_pid_control(PID_TypeDef *PID,float feedback_value);

#endif
