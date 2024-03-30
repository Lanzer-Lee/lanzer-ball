#include "stm32f10x.h"                
#include "Delay.h"
#include "motor.h"
#include "Serial.h"
#include "openmv.h"
#include "TIMER.h"
#include "control.h"
#include "echo.h"
#include "IMU.h"
#include "IIC.h"

uint8_t demo_status=0;

void set_up(void){
	Serial_USARTx_Init();
	IIC_Init();
	TIM_Init();
	pid_init();
	echo_init();
	//IMU_Init();
	set_servo_angle(1,200,2000);
	Delay_ms(1000);	
}

void debug_command_process(void){
	if(Serial_RxFlag_USART1==1){
		if(Serial_RxPacket_USART1[0]=='$'){
			if(Serial_RxPacket_USART1[1]=='>') position_pid_enable=1;
			if(Serial_RxPacket_USART1[1]=='<') angle_pid_enable=1;
			if(Serial_RxPacket_USART1[1]=='0'){
				position_pid_enable=0;
				angle_pid_enable=0;
			}
			Serial_SendString(USART1,Serial_RxPacket_USART1);
		}
		if(Serial_RxPacket_USART1[0]=='@'||Serial_RxPacket_USART1[0]=='#'){
			Serial_SendString(USART1,Serial_RxPacket_USART1);
			Serial_SendString(USART3,Serial_RxPacket_USART1);
		}
		Serial_RxFlag_USART1=0;
	}	
}

int main(void)
{
	set_up();
	while (1){
		//IMU_Data_Process();										
		debug_command_process();
		if(Serial_RxFlag_USART2==1){
			//Serial_SendString(USART1,Serial_RxPacket_USART2);
			openmv_data_process();
			printf("openmv=%f\r\n",position_pid.Error);
			Serial_RxFlag_USART2=0;
		}		
	}
}
