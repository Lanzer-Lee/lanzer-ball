#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"
#include "sys.h"
#if 1
#define IMU_IN()  {GPIOB->CRL&=0XFFFFF0FF;GPIOB->CRL|=(uint32_t)8<<8;}
#define IMU_OUT() {GPIOB->CRL&=0XFFFFF0FF;GPIOB->CRL|=(uint32_t)3<<8;}
	 
#define I2C_SCL    PBout(1) //SCL
#define I2C_SDA    PBout(2) //SDA
#define IMU_READ_SDA   PBin(2) 

void Delay(u32 count);
void I2C_IMU_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
u8 I2C_Wait_Ack(void);
void I2C_Ack(void);
void I2C_NAck(void);
void I2C_Send_Byte(u8 txd);
u8 I2C_Read_Byte(unsigned char ack);
int32_t I2CreadBytes(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length);
int32_t I2CwriteBytes(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length);

#endif
#endif
