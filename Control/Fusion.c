#include "Fusion.h"

Fusion_TypeDef fusion;

void Fusion_Init(Fusion_TypeDef *Fusion){
    Fusion->Enable=DISABLE;
    Fusion->Directin=MODE_HORIZONTAL;
    Fusion->LowerBound=0;
    Fusion->UpperBound=0;
    Fusion->MoveSpeed=0;
}

void Fusion_Set(Fusion_TypeDef *Fusion,uint16_t lower_bound,uint16_t upper_bound,uint8_t direction,int8_t speed){
    Fusion->LowerBound=lower_bound;
    Fusion->UpperBound=upper_bound;
    Fusion->Directin=direction;
    Fusion->MoveSpeed=speed;
}

void Fusion_FindBall(Fusion_TypeDef *Fusion){
    switch (Fusion->Directin){
        case MODE_HORIZONTAL:Motor_Horizontal(Fusion->MoveSpeed);break;
        case MODE_STRAIGHT:Motor_Straight(Fusion->MoveSpeed);break;
        case MODE_ROTE:Motor_Rote(Fusion->MoveSpeed);break;
        default:break;
    }
    Fusion->Enable=ENABLE;
}

void Fusion_AssertBall(Fusion_TypeDef *Fusion){
    if(cv.Flag==0){
        Motor_Horizontal(Fusion->MoveSpeed);
        Delay_ms(1500);
        Fusion_FindBall(Fusion);
    }
}

void Fusion_Detect(Fusion_TypeDef *Fusion){
    if(Fusion->Enable==ENABLE){
        printf("tof=%.1f\r\n",tof.Distance);
        if(Fusion->LowerBound<=tof.Distance && tof.Distance<=Fusion->UpperBound){
            printf("tof find ball\r\n");
            Fusion->Enable=DISABLE;
            Motor_Stop(&motor);
        }
    }   
}

