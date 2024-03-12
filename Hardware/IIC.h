#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"
#include "sys.h"
#include "Delay.h"

#define SDA_IN()    {GPIOB->CRL&=0x0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT()   {GPIOB->CRL&=0x0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
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

#endif
