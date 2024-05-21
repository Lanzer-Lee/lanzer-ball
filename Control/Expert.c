#include "Expert.h"

Expert_TypeDef expert;

void Expert_Init(Expert_TypeDef *Expert){
    Expert->SetPoint=0.0;
    Expert->ActualValue=0.0;
    Expert->Error=0.0;
    Expert->pFeedbackValue=NULL;
    Expert->ControlValue=0;
    Expert->pMotorCallback=NULL;
    Expert->Mode=MODE_HORIZONTAL;
    Expert->Enable=DISABLE;
}

void Expert_Set(Expert_TypeDef *Expert,float target,uint8_t mode){
    Expert->SetPoint=target;
    Expert->Mode=mode;
    Expert->ControlValue=0;
    switch (mode){
        case MODE_STRAIGHT:
            Expert->pMotorCallback=Motor_Straight;
            Expert->pFeedbackValue=&tof.Distance;
            break;
        case MODE_HORIZONTAL:
            Expert->pMotorCallback=Motor_Horizontal;
            Expert->pFeedbackValue=&cv.X;
            break;
        case MODE_ROTE:
            Expert->pMotorCallback=Motor_Rote;
            Expert->pFeedbackValue=&cv.X;
            break;
        case MODE_LINE:
            Expert->pMotorCallback=Motor_Straight;
            Expert->pFeedbackValue=&cv.Y;
            break;
        default:break;
    }
}

void Expert_Enable(Expert_TypeDef *Expert){
    Expert->Enable=ENABLE;
    TIM_Cmd(TIM3,ENABLE);
}

void Expert_Disable(Expert_TypeDef *Expert){
    Expert->Enable=DISABLE;
    TIM_Cmd(TIM3,DISABLE);
    //Motor_Stop(&motor);
}

void Expert_Display(Expert_TypeDef *Expert){
    printf("target = %.1f\r\n",Expert->SetPoint);
    printf("Error = %.1f\r\n",Expert->Error);
    printf("Feedback = %.1f\r\n",*Expert->pFeedbackValue);
}

int8_t Expert_Update(Expert_TypeDef *Expert){
    Expert->Error=(float)(Expert->SetPoint-*(Expert->pFeedbackValue));
    if((Expert->Error>=-POSITION_DEADLINE)&&(Expert->Error<=POSITION_DEADLINE)){
        Expert_Disable(Expert);
        Motor_Stop(&motor);
        return 0;
    }
    //Expert_Display(Expert);
    if(Expert->Error>=0) return 10;
    else if(Expert->Error<0) return -10;
    return 0;
}

void Expert_Control(Expert_TypeDef *Expert){
    if(Expert->Enable==ENABLE){
        
        switch (Expert->Mode){
            case MODE_STRAIGHT:TOF_GetData(&tof);break;
            default:openmv_analysis(&cv);break;
        } 
        
        if(Expert->Mode==MODE_HORIZONTAL) Expert->pMotorCallback(-Expert->ControlValue);
        else Expert->pMotorCallback(Expert->ControlValue); 
        Expert->ControlValue=Expert_Update(Expert);
    }
}
