#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x.h"                  
#include <stdio.h>
#include <stdarg.h>
#include "motor.h"

extern char Serial_RxPacket[];
extern uint8_t Serial_RxFlag;

void Serial_USARTx_Init(void);
void Serial_USART1_Init(int bound);
void Serial_USART2_Init(int bound);
void Serial_USART3_Init(int bound);
void Serial_SendByte(USART_TypeDef* USARTx,uint8_t Byte);
void Serial_SendString(USART_TypeDef* USARTx,char *String);
void Serial_SendArray(USART_TypeDef* USARTx,uint8_t *Array, uint16_t Length);
void Serial_SendNumber(USART_TypeDef* USARTx,uint32_t Number, uint8_t Length);
void Serial_SendString_Length(USART_TypeDef* USARTx,char *String,uint8_t len);
void Serial_USART1_SendByte(uint8_t Byte);
void Serial_USART1_SendString(char *String);
void Serial_USART1_SendArray(uint8_t *Array, uint16_t Length);
void Serial_USART1_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);
void Serial_USART2_SendByte(uint8_t Byte);
void Serial_USART2_SendString(char *String);
void Serial_USART2_SendArray(uint8_t *Array, uint16_t Length);
void Serial_USART2_SendNumber(uint32_t Number, uint8_t Length);
void Serial_USART3_SendByte(uint8_t Byte);
void Serial_USART3_SendString(char *String);
void Serial_USART3_SendArray(uint8_t *Array, uint16_t Length);
void Serial_USART3_SendNumber(uint32_t Number, uint8_t Length);
uint8_t instruction_in_motionset(uint8_t instruction);

#endif
