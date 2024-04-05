#include "openmv.h"

Openmv_TypeDef openmv;

void openmv_init(void){
    openmv.x=0;
    openmv.y=0;
    openmv.distance=0.0;
}

void openmv_data_process(void){

}

void openmv_analysis(void){
    if(Serial_RxFlag_USART2==1){
        sscanf(Serial_RxPacket_USART2,"(%d,%d,%f)",&openmv.x,&openmv.y,&openmv.distance);
        Serial_RxFlag_USART2=0;
    }
}
