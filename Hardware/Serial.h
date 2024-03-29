#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x.h"                  
#include <stdio.h>
#include <stdarg.h>
#include "servo.h"
#include "motor.h"
#include "control.h"

#define END_FLAG    '!'

extern char Serial_RxPacket_USART1[];
extern uint8_t Serial_RxFlag_USART1;
extern char Serial_RxPacket_USART2[];
extern uint8_t Serial_RxFlag_USART2;

void Serial_USARTx_Init(void);
void Serial_USART1_Init(int bound);
void Serial_USART2_Init(int bound);
void Serial_USART3_Init(int bound);
void Serial_SendByte(USART_TypeDef* USARTx,uint8_t Byte);
void Serial_SendString(USART_TypeDef* USARTx,char *String);
void Serial_SendArray(USART_TypeDef* USARTx,uint8_t *Array, uint16_t Length);
void Serial_SendNumber(USART_TypeDef* USARTx,uint32_t Number, uint8_t Length);
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

#endif
