#include "valve.h"

void valve_init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}

void valve_hit(uint16_t time){
    GPIO_SetBits(GPIOA,GPIO_Pin_4);
    Delay_ms(time);
    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}
