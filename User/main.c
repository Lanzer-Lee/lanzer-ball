#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "IIC.h"
#include "motor.h"

void set_up(void){
	IIC_Init();
	motor_init();
}

int main(void)
{
	set_up();
	while (1)
	{
		set_velocity(10,10,10,10);
		Delay_ms(500);
		set_velocity(-10,-10,-10,-10);
		Delay_ms(500);
	}
}
