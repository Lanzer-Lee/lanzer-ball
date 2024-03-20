#include "control.h"

PID_TypeDef g_speed_pid;

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

int16_t increment_pid_control(PID_TypeDef *PID,float feedback_value){
    PID->Error=(float)(PID->SetPoint-feedback_value);                                                     
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          
                        + (PID->Integral * PID->Error)                                             
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError)); 
    PID->PrevError = PID->LastError;                                       
    PID->LastError = PID->Error;
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

uint8_t aim_ball_mid(void){
    if(0<=target_x && target_x<157){
        standard_left(100,100);
        return NOTMID;
    }
    if(target_x>163){
        standard_right(100,100);
        return NOTMID;
    }
    if(157<=target_x && target_x<=163){
        return MID;
    }
    return NOTMID;
}

uint8_t find_ball_mid(void){
    standard_clockwise(100,100);
    if(target_x>=0){
        return MID;
    }
    return NOTMID;
}
