#include "openmv.h"

Openmv_TypeDef openmv_structure;

void openmv_init(void){
    openmv_structure.target_x=0;
    openmv_structure.target_y=0;
    openmv_structure.target_distance=0.0;
}

void openmv_data_process(void){
    openmv_structure.target_x=0;
    uint8_t i=2;
    while(Serial_RxPacket_USART2[i]!=')'){
        openmv_structure.target_x=openmv_structure.target_x*10+Serial_RxPacket_USART2[i++]-'0';
    }
    /*
    if(Serial_RxPacket_USART2[1]=='-'){
        target_x=-target_x;
    }
    */
}
