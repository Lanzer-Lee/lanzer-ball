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
	set_servo_angle(1,200,2000);
	Delay_ms(1000);
	TIM_Init();
	pid_init();
	set_pid_target(80);
	echo_init();
	IMU_Init();
	PID_Status=0;
}

void loop_demo_aim(void){
	if(g_speed_pid.SetPoint-2< target_x && target_x <g_speed_pid.SetPoint+2){
		standard_stop();
		demo_status=1;
	} 
	if(target_x>=g_speed_pid.SetPoint+2) standard_right(10);
    if(0<=target_x && target_x <=g_speed_pid.SetPoint-2) standard_left(10);
}

void loop_demo_ack(void){
	echo_distance=measure_distance();
	//printf("echo=%f\r\n",echo_distance);
	if(echo_distance>1.5) standard_forward(10);
	else{
		standard_stop();
		demo_status=2;
	}
}

int main(void)
{
	set_up();
	while (1){
		IMU_Data_Process();
		//if(demo_status==0) loop_demo_aim();	
		//if(demo_status==1) loop_demo_ack();										
		if(Serial_RxFlag_USART1==1){
			PID_Status=0;
			standard_stop();
			Delay_ms(2);
			if(Serial_RxPacket_USART1[0]=='$') PID_Status=1;
			Serial_SendString(USART1,Serial_RxPacket_USART1);
			Serial_SendString(USART3,Serial_RxPacket_USART1);
			Serial_RxFlag_USART1=0;
		}	
		if(Serial_RxFlag_USART2==1){
			//Serial_SendString(USART1,Serial_RxPacket_USART2);
			openmv_data_process();
			//printf("v=%f\r\n",g_speed_pid.ActualValue);
			//printf("int v=%d\r\n",(int16_t)(g_speed_pid.ActualValue));
			Serial_RxFlag_USART2=0;
		}	
		
	}
}
