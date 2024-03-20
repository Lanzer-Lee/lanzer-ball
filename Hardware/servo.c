#include "servo.h"

char servo_cmd[20];

void set_servo_angle(uint8_t servo_id,uint16_t servo_angle,uint16_t servo_time){
    sprintf(servo_cmd,"#%03dP%04dT%04d!",servo_id,servo_angle,servo_time);
    Serial_SendString(USART3,servo_cmd);
    Serial_SendString(USART1,servo_cmd);
}

void lift_ball(void){
    set_servo_angle(1,100,1500);
    Delay_ms(10);
}

void drop_ball(void){
    set_servo_angle(1,600,1500);
    Delay_ms(10);
}
