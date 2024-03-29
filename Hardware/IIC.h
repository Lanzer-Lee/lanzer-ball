#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"
#include "sys.h"
#include "Delay.h"

#define SDA_IN()    {GPIOB->CRH&=0xFFF0FFFF;GPIOB->CRH|=(uint32_t)8<<16;}
#define SDA_OUT()   {GPIOB->CRH&=0xFFF0FFFF;GPIOB->CRH|=(uint32_t)3<<16;}
#define IIC_SCL     PBout(1)
#define IIC_SDA     PBout(12)
#define READ_SDA    PBin(12)

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
uint8_t IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(uint8_t txd);
uint8_t IIC_Read_Byte(uint8_t ack);
uint8_t IIC_Read_Bytes(uint8_t address,uint8_t reg,uint8_t *buf,uint8_t len);
int8_t IIC_Send_Bytes(int8_t address,int8_t reg,int8_t *buf,int8_t len);
uint8_t IIC_Read_Bytes_Encoder(uint8_t address,uint8_t reg,uint8_t *buf,uint8_t len);

#endif
