#include "servo.h"

char servo_cmd[3*SERVO_NUM+7];
uint16_t servo_time=0,servo_angle=0;
uint8_t servo_id=0;

void servo_init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void servo_send_cmd(uint8_t id,uint16_t time, uint16_t angle){
    uint32_t check_sum=0;
    uint8_t data_len=0x07,i=0;
    servo_cmd[0]=0x55;
    servo_cmd[1]=0x55;
    servo_cmd[2]=id;
    servo_cmd[3]=data_len;
    servo_cmd[4]=SERVO_MOVE_TIME_WRITE;
    servo_cmd[5]=(uint8_t)(angle);
    servo_cmd[6]=(uint8_t)(angle>>8);
    servo_cmd[7]=(uint8_t)(time);
    servo_cmd[8]=(uint8_t)(time>>8);
    for(i=2;i<=data_len+1;i++){
        check_sum+=servo_cmd[i];
    }
    servo_cmd[data_len+2]=~check_sum;
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
    Serial_SendString_Length(USART2,servo_cmd,data_len+3);
}

void servo_data_process(void){
    servo_id=Serial_RxPacket[3]-'0';
    servo_angle=(Serial_RxPacket[5]-'0')*1000+(Serial_RxPacket[6]-'0')*100+(Serial_RxPacket[7]-'0')*10+(Serial_RxPacket[8]-'0');
    servo_time=(Serial_RxPacket[10]-'0')*1000+(Serial_RxPacket[11]-'0')*100+(Serial_RxPacket[12]-'0')*10+(Serial_RxPacket[13]-'0');
}
