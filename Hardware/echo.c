#include "echo.h"

__IO float echo_diatance=0.0;

void echo_init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

float echo_measure_distance(void){
    float pulse_width = 0.0;
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==1){} 
    GPIO_SetBits(GPIOA, GPIO_Pin_6);    
    Delay_us(30);
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)){}
	TIM_SetCounter (TIM2,0);
    TIM_Cmd(TIM2, ENABLE);
    while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)){}
    TIM_Cmd(TIM2, DISABLE);
    pulse_width = TIM_GetCounter (TIM2);
    return pulse_width * 0.017;
}

void echo_aim_ball(void){
    echo_diatance=echo_measure_distance();
    Motor_Straight(TACKLE_SPEED);
    while(1){
        if(echo_diatance<TACKLE_DISTANCE){
            Motor_Stop(&motor);
            return;
        }
        echo_diatance=echo_measure_distance();
    }
}
