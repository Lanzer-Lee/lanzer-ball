#ifndef __TOF_H
#define __TOF_H

#include "stm32f10x.h"
#include "Serial.h"
#include <string.h>
#include "openmv.h"

#define TOF_DATA_LEN    18

#define TOF_BAUD230400  0x00
#define TOF_BAUD460800  0x01
#define TOF_BAUD512000  0x02
#define TOF_BAUD921600  0x03
#define TOF_BAUD1500000  0x04

#define TOF_FREQ10  0x00
#define TOF_FREQ100  0x01
#define TOF_FREQ200  0x02
#define TOF_FREQ500  0x03
#define TOF_FREQ1000  0x04
#define TOF_FREQ1800  0x05

#define TOF_FAR_BOUND     2000
#define TOF_NEAR_BOUND    960 
#define TOF_LIFT_DISTANCE   470

typedef struct{
    uint8_t SendBuffer[TOF_DATA_LEN];
    uint8_t RxBufferOK[TOF_DATA_LEN];
    uint8_t RxBufferTemp[TOF_DATA_LEN];
    uint8_t SensorData[TOF_DATA_LEN];
    __IO float Distance;
    uint8_t Energy;
    uint8_t Noise;
}TOF_TypeDef;

extern TOF_TypeDef tof;

uint8_t TOF_CountSum(uint8_t *buf);
void TOF_Init(TOF_TypeDef *TOF);
void TOF_Stop(TOF_TypeDef *TOF);
void TOF_Start(TOF_TypeDef *TOF);
void TOF_SetStandard(TOF_TypeDef *TOF);
void TOF_SetBaudrate(TOF_TypeDef *TOF,uint8_t TOF_BAUD);
void TOF_SetFrequency(TOF_TypeDef *TOF,uint8_t TOF_FREQ);
void TOF_Decode(TOF_TypeDef *TOF,uint8_t RxData);
uint8_t TOF_GetData(TOF_TypeDef *TOF);
uint8_t TOF_Scan(TOF_TypeDef *TOF,uint16_t lower_bound,uint16_t upper_bound);
void TOF_Find_Ball(TOF_TypeDef *TOF,uint8_t direction);
void TOF_Aim_Ball(TOF_TypeDef *TOF);

#endif
