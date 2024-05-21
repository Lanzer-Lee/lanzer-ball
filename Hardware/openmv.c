#include "openmv.h"

Openmv_TypeDef cv;

void openmv_init(Openmv_TypeDef *CV){
    CV->X=-2;
    CV->Y=-2;
    CV->Distance=-2;
    CV->Slope=-2;
    CV->State=OPENMV_NULL;
    CV->Flag=0;
    CV->Command[0]='\0';
}

void openmv_reset(Openmv_TypeDef *CV){
    CV->X=-1;
    CV->Flag=0;
}

void openmv_assert(Openmv_TypeDef *CV){
    openmv_analysis(CV);
    if(CV->State==OPENMV_BASKETBALL||CV->State==OPENMV_VOLLEYBALL){
        if(CV->X>0) CV->Flag=1;
    }
}

void openmv_set(Openmv_TypeDef *CV,uint8_t state){
    CV->State=state;
    sprintf(CV->Command,"%1d",CV->State);
    Serial_SendString(USART2,CV->Command);
}

void openmv_analysis(Openmv_TypeDef *CV){
    if(Serial_RxFlag_USART2==1){
        switch (CV->State){
            case OPENMV_LINE:sscanf(Serial_RxPacket_USART2,"(%f)",&CV->Distance);break;
            default: sscanf(Serial_RxPacket_USART2,"(%f)",&CV->X);break;
        }
        //printf("openmv get data:\t");
        //printf(Serial_RxPacket_USART2);
        //printf("\r\n");
        Serial_RxFlag_USART2=0;
    }
}

uint8_t openmv_find_ball(Openmv_TypeDef *CV,uint8_t search_direction){
    openmv_analysis(&cv);
    //printf("%.1f\r\n",CV->X);
    if(CV->X<0){
        switch (search_direction){
            case OPENMV_SEARCH_LEFT: Motor_Horizontal(-OPENMV_SEARCH_SPEED);break;
            case OPENMV_SEARCH_RIGHT: Motor_Horizontal(OPENMV_SEARCH_SPEED);break;
            default: break;
        }
        return 0;
    }
    return 1;
}

void openmv_aim_ball(Openmv_TypeDef *CV,uint8_t search_direction){
    Expert_Set(&expert,OPENMV_SCREEN_MID,MODE_HORIZONTAL);
    //pid_set(&pid,OPENMV_SCREEN_MID,MODE_HORIZONTAL);
    uint8_t flag=openmv_find_ball(CV,search_direction);
    while(!flag){
        flag=openmv_find_ball(CV,search_direction);
        //Delay_us(5);
    }
    Motor_Stop(&motor);
    Delay_ms(1);
    Motor_Stop(&motor);
    Delay_ms(1);
    //pid_enable(&pid);
    Expert_Enable(&expert);
}
