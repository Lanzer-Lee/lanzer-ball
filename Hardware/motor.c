#include "motor.h"

uint8_t voltage[3]={0};
uint32_t encoder_total[MOTOR_NUM]={0};
int8_t velocity[MOTOR_NUM]={0};
char motor_cmd[20];
char stop_cmd[]="@0000000000000000!";

void set_velocity_fixtime(int8_t left_forward,int8_t right_forward,int8_t left_back,int8_t right_back,int time){
	uint8_t i=0;
	sprintf(motor_cmd,"@%04d%04d%04d%04d!",left_forward,right_forward,left_back,right_back);
    for(i=0;i<18;i++)
        if(motor_cmd[i]=='-')
            motor_cmd[i]='1';
    Serial_SendString(USART3,motor_cmd);
	//Serial_SendString(USART1,motor_cmd);
    Delay_ms(time);
    standard_stop();
    Delay_ms(10);
}

void set_velocity_auto_fixtime(int time){
    set_velocity_fixtime(velocity[0],velocity[1],velocity[2],velocity[3],time);
}

void standard_forward_fixtime(int8_t motor_velocity,int time){
    set_velocity_fixtime(motor_velocity,motor_velocity,motor_velocity,motor_velocity,time);
}

void standard_backward_fixtime(int8_t motor_velocity,int time){
    set_velocity_fixtime(-motor_velocity,-motor_velocity,-motor_velocity,-motor_velocity,time);
}

void standard_left_fixtime(int8_t motor_velocity,int time){
    set_velocity_fixtime(motor_velocity,-motor_velocity,-motor_velocity,motor_velocity,time);
}

void standard_right_fixtime(int8_t motor_velocity,int time){
    set_velocity_fixtime(-motor_velocity,motor_velocity,motor_velocity,-motor_velocity,time);
}

void standard_clockwise_fixtime(int8_t motor_velocity,int time){
    set_velocity_fixtime(motor_velocity,-motor_velocity,motor_velocity,-motor_velocity,time);
}

void standard_counterclockwise_fixtime(int8_t motor_velocity,int time){
    set_velocity_fixtime(-motor_velocity,motor_velocity,-motor_velocity,motor_velocity,time);
}

void standard_stop(void){
    Serial_SendString(USART3,stop_cmd);
    Delay_ms(1);
    //Serial_SendString(USART1,stop_cmd);
}

void set_velocity(int8_t left_forward,int8_t right_forward,int8_t left_back,int8_t right_back){
	uint8_t i=0;
	sprintf(motor_cmd,"@%04d%04d%04d%04d!",left_forward,right_forward,left_back,right_back);
    for(i=0;i<18;i++)
        if(motor_cmd[i]=='-')
            motor_cmd[i]='1';
    Serial_SendString(USART3,motor_cmd);
    Delay_ms(1);
	//Serial_SendString(USART1,motor_cmd);
}

void set_velocity_auto(void){
    set_velocity(velocity[0],velocity[1],velocity[2],velocity[3]);
}

void standard_forward(int8_t motor_velocity){
    set_velocity(motor_velocity,motor_velocity,motor_velocity,motor_velocity);
}

void standard_backward(int8_t motor_velocity){
    set_velocity(-motor_velocity,-motor_velocity,-motor_velocity,-motor_velocity);
}

void standard_left(int8_t motor_velocity){
    set_velocity(motor_velocity,-motor_velocity,-motor_velocity,motor_velocity);
}

void standard_right(int8_t motor_velocity){
    set_velocity(-motor_velocity,motor_velocity,motor_velocity,-motor_velocity);
}

void standard_clockwise(int8_t motor_velocity){
    set_velocity(motor_velocity,-motor_velocity,motor_velocity,-motor_velocity);
}

void standard_counterclockwise(int8_t motor_velocity){
    set_velocity(-motor_velocity,motor_velocity,-motor_velocity,motor_velocity);
}
