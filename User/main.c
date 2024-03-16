#include "stm32f10x.h"                
#include "Delay.h"
#include "IIC.h"
#include "motor.h"
#include "Serial.h"
#include "LED.h"
#include "Key.h"

void set_up(void){
	Serial_USARTx_Init();
	LED_Init();
	IIC_Init();
}

int main(void)
{
	set_up();
	Delay_ms(1000);
	while (1){
		/*
		Serial_SendString(USART3,"@0100010001000100!");
		Delay_ms(800);
		Serial_SendString(USART3,"@1100010001001100!");
		Delay_ms(800);
		Serial_SendString(USART3,"@1100110011001100!");
		Delay_ms(800);
		Serial_SendString(USART3,"@0100110011000100!");
		Delay_ms(800);
		*/
		if(Serial_RxFlag==1){
			Serial_SendString(USART1,Serial_RxPacket);
			Serial_SendString(USART3,Serial_RxPacket);
			Serial_RxFlag=0;
		}		
	}
}
