#include "pid.h"

PID_TypeDef pid;

void pid_init(PID_TypeDef *PID){
    PID->SetPoint=0.0;
    PID->ActualValue=0.0;
    PID->SumError=0.0;
    PID->Error=0.0;
    PID->LastError=0.0;
    PID->PrevError=0.0;
    PID->ControlValue=0.0;
    PID->Proportion=KP_POSITION;
    PID->Integral=KI_POSITION;
    PID->Derivative=KD_POSITION;
    PID->pFeedbackValue=NULL;
    PID->pMotorCallback=NULL;
    PID->Mode=MODE_HORIZONTAL;
    PID->Enable=DISABLE;
}

void pid_set(PID_TypeDef *PID,float target,uint8_t mode){
    PID->SetPoint=target;
    PID->Mode=mode;
    PID->ControlValue=0.0;
    switch (mode){
        case MODE_STRAIGHT:
            PID->pMotorCallback=Motor_Straight;
            PID->pFeedbackValue=&tof.Distance;
        break;
        case MODE_HORIZONTAL:
            PID->pMotorCallback=Motor_Horizontal;
            PID->pFeedbackValue=&cv.X;
        break;
        case MODE_ROTE:
            PID->pMotorCallback=Motor_Rote;
            PID->pFeedbackValue=&cv.X;
        break;
        default:break;
    }
}

void pid_set_parameter(PID_TypeDef *PID,float Kp,float Ki,float Kd){
    PID->Proportion=Kp;
    PID->Integral=Ki;
    PID->Derivative=Kd;
}

void pid_enable(PID_TypeDef *PID){
    PID->Enable=ENABLE;
    TIM_Cmd(TIM3,ENABLE);
}

void pid_disable(PID_TypeDef *PID){
    PID->Enable=DISABLE;
    TIM_Cmd(TIM3,DISABLE);
    Motor_Stop(&motor);
}

float pid_update(PID_TypeDef *PID){
    /*compute error*/
    PID->Error=(float)(PID->SetPoint-*(PID->pFeedbackValue));
    /*compute deadline*/
    if((PID->Error>=-POSITION_DEADLINE)&&(PID->Error<=POSITION_DEADLINE)){
        pid_disable(PID);
        Motor_Stop(&motor);;
        printf("target aimed!\r\n");
        printf("target=%.1f",PID->SetPoint);
        printf("feedback=%.1f,control=%.1f,error=%.1f\r\n",*(PID->pFeedbackValue),PID->ActualValue,PID->Error);
        return 0;
    } 
    /*intergral bound*/ 
    //if(PID->Error>POSITION_INTERGRAL_BOUND) PID->Error=POSITION_INTERGRAL_BOUND;
    //if(PID->Error<-POSITION_INTERGRAL_BOUND) PID->Error=-POSITION_INTERGRAL_BOUND;                                           
    /*compute output*/
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          
                        + (PID->Integral * PID->Error)                                             
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));
    /*output bound*/ 
    if(PID->ActualValue>SPEED_UPPER_BOUND) PID->ActualValue=SPEED_UPPER_BOUND;
    else if(PID->ActualValue<-SPEED_UPPER_BOUND) PID->ActualValue=-SPEED_UPPER_BOUND;
    else if(0<=PID->ActualValue && PID->ActualValue<SPEED_LOWER_BOUND) PID->ActualValue=SPEED_LOWER_BOUND;
    else if(-SPEED_LOWER_BOUND<PID->ActualValue && PID->ActualValue<0) PID->ActualValue=-SPEED_LOWER_BOUND;
    /*update error*/
    PID->PrevError = PID->LastError;                                       
    PID->LastError = PID->Error;
    printf("target=%.1f",PID->SetPoint);
    printf("feedback=%.1f,control=%.1f,error=%.1f\r\n",*(PID->pFeedbackValue),PID->ActualValue,PID->Error);
    return PID->ActualValue;
}

void pid_control(PID_TypeDef *PID){
    if(PID->Enable==ENABLE){   
        
        switch (PID->Mode){
            case MODE_STRAIGHT:TOF_GetData(&tof);break;
            case MODE_HORIZONTAL:openmv_analysis(&cv);break;
            case MODE_ROTE:openmv_analysis(&cv);break;
            default:break;
        } 
        
        if(PID->Mode==MODE_HORIZONTAL) PID->pMotorCallback(-(int8_t)(PID->ControlValue));
        else PID->pMotorCallback((int8_t)(PID->ControlValue)); 
        PID->ControlValue=pid_update(PID);                         
        //printf("feedback=%.1f,control=%d\r\n",*(PID->pFeedbackValue),(int8_t)(speed_control_value));
    }
}

