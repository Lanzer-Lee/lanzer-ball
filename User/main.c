#include "stm32f10x.h"                
#include "Delay.h"
#include "motor.h"
#include "Serial.h"
#include "openmv.h"

void set_up(void){
	Serial_USARTx_Init();
	set_servo_angle(1,200,2000);
	Delay_ms(1000);
}

void demo(void){
	drop_ball();
	standard_forward(100,1000);
	lift_ball();
	Delay_ms(2000);
	drop_ball();
	standard_backward(100,1000);
	standard_clockwise(100,3000);
	standard_forward(100,1500);
	standard_counterclockwise(100,2500);
	standard_left(100,1000);
	standard_right(100,1000);
	standard_backward(100,1000);
	standard_stop();
}

int main(void)
{
	set_up();
	//demo();
	while (1){
		if(Serial_RxFlag_USART1==1){
			Serial_SendString(USART1,Serial_RxPacket_USART1);
			Serial_SendString(USART3,Serial_RxPacket_USART1);
			Serial_RxFlag_USART1=0;
		}	
		if(Serial_RxFlag_USART2==1){
			Serial_SendString(USART1,Serial_RxPacket_USART2);
			openmv_data_process();
			Serial_RxFlag_USART2=0;
		}	
		
	}
}
