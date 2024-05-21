#include "power.h"

void Power_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin =GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}

void Power_Set(FunctionalState NewState){
    switch (NewState){
        case ENABLE:GPIO_SetBits(GPIOA, GPIO_Pin_5);break;
        default:GPIO_ResetBits(GPIOA, GPIO_Pin_5);break;
    }
}
