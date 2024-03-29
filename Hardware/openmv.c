#include "openmv.h"

int16_t target_x=0;

void openmv_data_process(void){
    target_x=0;
    uint8_t i=2;
    while(Serial_RxPacket_USART2[i]!=')'){
        target_x=target_x*10+Serial_RxPacket_USART2[i++]-'0';
    }
    /*
    if(Serial_RxPacket_USART2[1]=='-'){
        target_x=-target_x;
    }
    */
}
