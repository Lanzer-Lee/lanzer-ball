#include "servo.h"

Servo_TypeDef servo;

void servo_init(Servo_TypeDef *Servo){
    Servo->Angle=100;
    Servo->Time=SERVO_MOVE_TIME;
    Servo->ID=SERVO_ID;
    servo_control(Servo);
}
#if 0
void servo_control(Servo_TypeDef *Servo){
    uint32_t check_sum=0;
    uint8_t data_len=0x07,i=0;
    Servo->Command[0]=0x55;
    Servo->Command[1]=0x55;
    Servo->Command[2]=Servo->ID;
    Servo->Command[3]=data_len;
    Servo->Command[4]=SERVO_WRITE;
    Servo->Command[5]=(uint8_t)(Servo->Angle);
    Servo->Command[6]=(uint8_t)(Servo->Angle>>8);
    Servo->Command[7]=(uint8_t)(Servo->Time);
    Servo->Command[8]=(uint8_t)(Servo->Time>>8);
    for(i=2;i<=data_len+1;i++) check_sum+=Servo->Command[i];
    Servo->Command[data_len+2]=~check_sum;
    for(i=0;i<data_len+3;i++) Serial_SendByte(USART3,Servo->Command[i]);
}
#endif

void servo_control(Servo_TypeDef *Servo){  
    uint8_t i=0;
    Servo->Command[0]=0x55;
    Servo->Command[1]=0x55;  
    Servo->Command[2]=0x08;            
    Servo->Command[3]=0x03;          
    Servo->Command[4]=0x01;              
    Servo->Command[5]=(uint8_t)(Servo->Time);
    Servo->Command[6]=(uint8_t)(Servo->Time>>8); 
    Servo->Command[7]=0x01;           
    Servo->Command[8]=(uint8_t)(Servo->Angle);
    Servo->Command[9]=(uint8_t)(Servo->Angle>>8);
    for(i=0;i<10;i++) Serial_SendByte(USART3,Servo->Command[i]);
}

void servo_up(Servo_TypeDef *Servo){
    Servo->Angle=SERVO_UP_ANGLE;
    Servo->Time=SERVO_MOVE_TIME;
    Servo->ID=SERVO_ID;
    servo_control(Servo);
    Delay_ms(SERVO_MOVE_TIME);
}

void servo_down(Servo_TypeDef *Servo){
    Servo->Angle=SERVO_DOWN_ANGLE;
    Servo->Time=SERVO_MOVE_TIME;
    Servo->ID=SERVO_ID;
    servo_control(Servo);
    Delay_ms(SERVO_MOVE_TIME);
}

void servo_view_ball(Servo_TypeDef *Servo){
    Servo->Angle=SERVO_VIEW_ANGLE;
    Servo->Time=SERVO_MOVE_TIME;
    Servo->ID=SERVO_ID;
    servo_control(Servo);
}
