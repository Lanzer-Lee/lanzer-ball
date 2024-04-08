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
#include "debug.h"

uint8_t demo_status=0;

void set_up(void){
	Serial_USARTx_Init();
	IIC_Init();
	TIM_Init();
	pid_init();
	echo_init();
	IMU_Init();
	set_servo_angle(1,200,2000);
	Delay_ms(1000);	
}

int main(void)
{
	set_up();
	set_move(STRAIGHT);
	openmv_state_transfer(0);
	while (1){					
		debug_command_process();
		openmv_analysis();		
	}
}
