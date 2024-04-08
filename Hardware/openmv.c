#include "openmv.h"

Openmv_TypeDef openmv;
char openmv_command[5]="0";
char data_num=0;

void openmv_init(void){
    openmv.x=0.0;
    openmv.y=0.0;
    openmv.distance=0.0;
}

void openmv_state_transfer(uint8_t state){
    sprintf(openmv_command,"%1d",state);
    Serial_SendString(USART2,openmv_command);
}

void openmv_analysis(void){
    if(Serial_RxFlag_USART2==1){
        if(Serial_RxPacket_USART2[1]=='1'){
            sscanf(Serial_RxPacket_USART2,"(%c,%f)",&data_num,&openmv.distance);
            //printf("openmv.distance=%.2f\r\n",openmv.distance);
        }
        else if(Serial_RxPacket_USART2[1]=='3'){
            sscanf(Serial_RxPacket_USART2,"(%c,%f,%f,%f)",&data_num,&openmv.x,&openmv.y,&openmv.distance);
            //printf("openmv=%d,%d,%.2f\r\n",openmv.x,openmv.y,openmv.distance);
        }
        Serial_RxFlag_USART2=0;
    }
}

void laser_distance_control(float set_distance){
    openmv_state_transfer(STATE_LASER);
    set_pid_target(&position_pid,set_distance);
    set_pid_parameter(&position_pid,0.1,0.0,0.0);
    set_move(STRAIGHT);
    feedback_value=&(openmv.distance);
    pid_enable=1;
}

void find_ball(float target_pixel,uint8_t direction){
    openmv_state_transfer(STATE_BALL);
    set_pid_target(&position_pid,target_pixel);
    set_pid_parameter(&position_pid,0.1,0.0,0.0);
    set_move(direction);
    feedback_value=&(openmv.x);
    pid_enable=1;
}

void find_bucket(float target_pixel,uint8_t direction){
    openmv_state_transfer(STATE_BUCKET);
    set_pid_target(&position_pid,target_pixel);
    set_pid_parameter(&position_pid,0.1,0.0,0.0);
    set_move(direction);
    feedback_value=&(openmv.x);
    pid_enable=1;
}


