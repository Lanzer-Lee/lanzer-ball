#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"
#include "sys.h"
#include "Delay.h"

#define SDA_IN()    {GPIOB->CRL&=0xFFFFF0FF;GPIOB->CRL|=(uint32_t)8<<8;}
#define SDA_OUT()   {GPIOB->CRL&=0xFFFFF0FF;GPIOB->CRL|=(uint32_t)3<<8;}
#define IIC_SCL     PBout(1)
#define IIC_SDA     PBout(2)
#define READ_SDA    PBin(2)

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
uint8_t IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(uint8_t txd);
uint8_t IIC_Read_Byte(uint8_t ack);
uint8_t IIC_Read_Bytes(uint8_t address,uint8_t reg,uint8_t *buf,uint8_t len);
uint8_t IIC_Send_Bytes(uint8_t address,uint8_t reg,uint8_t *buf,uint8_t len);
int32_t IICreadBytes(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length);
int32_t IICwriteBytes(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length);

#endif
