#ifndef __CONTROL_H
#define __CONTROL_H

#include "openmv.h"
#include "motor.h"
#include "IMU.h"

/*pid parameter*/
#define SMAPLSE_PID_SPEED   50

#define KP_POSITION  0.30f
#define KI_POSITION  0.00f
#define KD_POSITION  0.00f

#define KP_ANGLE    0.45f
#define KI_ANGLE    0.00f
#define KD_ANGLE    0.00f

/*pid bound*/
#define SPEED_BOUND   20

#define ANGLE_DEADLINE  2
#define ANGLE_INTERGRAL_BOUND   45

#define POSITION_DEADLINE   3
#define POSITION_INTERGRAL_BOUND    15

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

extern PID_TypeDef position_pid;
extern PID_TypeDef angle_pid;
extern int8_t auto_velocity;
extern uint8_t angle_pid_enable;
extern uint8_t position_pid_enable;
extern uint8_t position_master_enable;
extern uint8_t angle_master_enable;

void pid_init(void);
void set_pid_target(PID_TypeDef *pid,float target);
void set_pid_parameter(PID_TypeDef *pid,float kp,float ki,float kd);
float angle_pid_update(PID_TypeDef *PID,float feedback_value);
void angle_pid_control(void);
float position_pid_update(PID_TypeDef *PID,float feedback_value);
void position_pid_control(void);
void master_position_control(float feedback_value);

#endif
