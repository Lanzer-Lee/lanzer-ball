#include "stm32f10x.h"                
#include "Delay.h"
#include "IIC.h"
#include "motor.h"
#include "attitude.h"
#include "series.h"
#include "Serial.h"
#include "GAME.h"
#include "debug.h"
#include "TIMER.h"
#include "valve.h"
#include "TOF.h"
#include "servo.h"
#include "openmv.h"
#include "pid.h"
#include "Key.h"
#include "IMU.h"
#include "I2C.h"
#include "echo.h"
#include "Expert.h"
#include "power.h"
#include "Fusion.h"
#include "OLED.h"

void set_up(void){
	SystemInit();
	Power_Init();
	Delay_Init();
	IIC_Init();
	//I2C_IMU_Init();
	Serial_USARTx_Init();
	Motor_Init(&motor);
	valve_init();
	TOF_Init(&tof);
	IMU_Init(&imu);
	servo_init(&servo);
	openmv_init(&cv);
	attitude_init(&robot);
	series_init(&series);
	game_init(&game);
	debug_init(&data);
	TIM_Init();
	pid_init(&pid);
	Expert_Init(&expert);
	Fusion_Init(&fusion);
	KEY_Init();
	EXTIX_Init();
	echo_init();
	OLED_Init();
	Motor_Stop(&motor);
}

int main(void)
{
	set_up();
	while (1){				
		game_play(&game);
	}
}
