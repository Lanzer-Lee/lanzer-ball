#include "valve.h"

uint16_t hit_time=0;

void valve_init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}

void valve_data_process(void){
    uint8_t i=0;
    for(i=1;Serial_RxPacket[i]!='!';i++){
        hit_time=hit_time*10+(Serial_RxPacket[i]-'0');
    }
}

void hit_ball(uint16_t time){
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
	Delay_ms(time);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}

