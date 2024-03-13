#include "stm32f10x.h"                  // Device header
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
	while (1){
		if(Serial_RxFlag==1){
			Serial_SendString(USART1,Serial_RxPacket);
			Serial_SendString(USART3,Serial_RxPacket);
			Serial_RxFlag=0;
		}		
	}
}
