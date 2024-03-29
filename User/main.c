#include "stm32f10x.h"                 
#include "Delay.h"
#include "IIC.h"
#include "motor.h"
#include "Serial.h"
#include "LED.h"
#include "servo.h"
#include "valve.h"

void set_up(void){
	Serial_USARTx_Init();
	LED_Init();
	IIC_Init();
	motor_init();
	servo_init();
	valve_init();
}

int main(void)
{
	set_up();
	while (1){
		if(Serial_RxFlag==1){
			Serial_SendString(USART1,Serial_RxPacket);
			if(Serial_RxPacket[0]=='@'){
				motor_data_process();
				set_velocity_auto();
			}
			if(Serial_RxPacket[0]=='#'){
				servo_data_process();
				servo_send_cmd(servo_id,servo_time,servo_angle);
			}
			if(Serial_RxPacket[0]=='$'){
				valve_data_process();
				hit_ball(hit_time);
				read_mileage();
				encoder_data_process();
				printf("encoder1=%ld,endcoder2=%ld,encoder3=%ld,encoder4=%ld \r\n",encoder_total[0],encoder_total[1],encoder_total[3],encoder_total[4]);
				//printf("voltage=%d\r\n",read_voltage());
			}
			Serial_RxFlag=0;
		}
	}
}
