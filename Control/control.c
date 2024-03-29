#include "control.h"

PID_TypeDef g_speed_pid;
int16_t auto_velocity=0;
uint8_t PID_Status=0;

void pid_init(void){
    g_speed_pid.SetPoint=0;
    g_speed_pid.ActualValue=0.0;
    g_speed_pid.SumError=0.0;
    g_speed_pid.Error=0.0;
    g_speed_pid.LastError=0.0;
    g_speed_pid.PrevError=0.0;
    g_speed_pid.Proportion=KP;
    g_speed_pid.Integral=KI;
    g_speed_pid.Derivative=KD;
}

void set_pid_target(float target){
    g_speed_pid.SetPoint=target;
}

int16_t increment_pid_control(PID_TypeDef *PID,float feedback_value){
    PID->Error=(float)(PID->SetPoint-feedback_value);                                                     
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          
                        + (PID->Integral * PID->Error)                                             
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError)); 
    PID->PrevError = PID->LastError;                                       
    PID->LastError = PID->Error;
    if(PID->ActualValue>SPEED_UPPER_BOUND) PID->ActualValue=SPEED_UPPER_BOUND;
    if(PID->ActualValue<SPEED_LOWER_BOUND) PID->ActualValue=SPEED_LOWER_BOUND;
    return ((int16_t)(PID->ActualValue));
}

int16_t position_pid_control(PID_TypeDef *PID,float feedback_value){
    PID->Error=(float)(PID->SetPoint-feedback_value);
    PID->SumError += PID->Error;
    PID->ActualValue = (PID->Proportion * PID->Error)                     
                       + (PID->Integral * PID->SumError)                    
                       + (PID->Derivative * (PID->Error - PID->LastError)); 
    PID->LastError = PID->Error;
    return ((int16_t)(PID->ActualValue));
}



