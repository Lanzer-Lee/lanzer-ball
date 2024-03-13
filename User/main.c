#include "stm32f10x.h"                 
#include "Delay.h"
#include "IIC.h"
#include "motor.h"
#include "Serial.h"
#include "LED.h"

void set_up(void){
	Serial_USARTx_Init();
	LED_Init();
	IIC_Init();
	motor_init();
}

void loop_motor(void){
		standard_forward(5);
		Delay_ms(2000);
		standard_backward(5);
		Delay_ms(2000);
		standard_left(5);
		Delay_ms(2000);
		standard_right(5);
		Delay_ms(2000);
}

int main(void)
{
	set_up();
	while (1){
		if(Serial_RxFlag==1){
			if(Serial_RxPacket[0]=='@'){
				switch (Serial_RxPacket[1])
				{
				case FORWARD:
					standard_forward(50);
					break;
				case BACKWARD:
					standard_backward(50);
					break;
				case LEFT:
					standard_left(50);
					break;
				case RIGHT:
					standard_right(50);
					break;
				case STOP:
					standard_stop();
					break;
				default:
					break;
				}
			}
			Serial_RxFlag=0;
		}
	}
}
