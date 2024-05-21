#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"
#include "sys.h"
#include "Delay.h"

//PB4 PG15
#define    IIC_IO_SDA      GPIO_Pin_12  //SDA的IO口
#define    IIC_IO_SCL      GPIO_Pin_10  //SCL的IO口
#define    GPIOX           GPIOE       //GPIOx选择
#define    CLOCK		   RCC_APB2Periph_GPIOE //时钟信号
 
#define    IIC_SCL         PEout(10) //SCL
#define    IIC_SDA         PEout(12) //输出SDA
#define    READ_SDA        PEin(12)  //输入SDA

//#define IIC_SDA_IN()    {GPIOE->CRH&=0xFFF0FFFF;GPIOE->CRH|=(uint32_t)(8<<16);}
//#define IIC_SDA_OUT()   {GPIOE->CRH&=0xFFF0FFFF;GPIOE->CRH|=(uint32_t)(3<<16);}

void IIC_SDA_OUT(void);
void IIC_SDA_IN(void);
void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Ack(void);
void IIC_NAck(void);
uint8_t IIC_Wait_Ack(void);
void IIC_Send_Byte(uint8_t txd);
uint8_t IIC_Read_Byte(uint8_t ack);
uint8_t IIC_Read_Bytes(uint8_t address,uint8_t Reg,uint8_t *Buf,uint8_t Len);
uint8_t IIC_Send_Bytes(uint8_t address,uint8_t Reg,int8_t *Buf,uint8_t Len);

#endif
