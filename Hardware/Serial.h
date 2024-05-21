#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x.h"
#include <stdarg.h>
#include <stdio.h>
#include "TOF.h"

#define PACKET_LEN  100

extern char Serial_RxPacket_USART1[];				
extern uint8_t Serial_RxFlag_USART1;	
extern char Serial_RxPacket_USART2[];				
extern uint8_t Serial_RxFlag_USART2;	
extern char Serial_RxPacket_USART3[];	
extern uint8_t Serial_RxFlag_USART3;		
extern char Serial_RxPacket_UART4[];	
extern uint8_t Serial_RxFlag_UART4;	
extern char Serial_RxPacket_UART5[];	
extern uint8_t Serial_RxFlag_UART5;

void Serial_USARTx_Init(void);
void Serial_USART1_Init(int bound);
void Serial_USART2_Init(int bound);
void Serial_USART3_Init(int bound);
void Serial_UART4_Init(int bound);
void Serial_UART5_Init(int bound);
uint32_t Serial_Pow(uint32_t X, uint32_t Y);
void Serial_SendByte(USART_TypeDef* USARTx,uint8_t Byte);
void Serial_SendString(USART_TypeDef* USARTx,char *String);
void Serial_SendArray(USART_TypeDef* USARTx,uint8_t *Array, uint16_t Length);
void Serial_SendNumber(USART_TypeDef* USARTx,uint32_t Number, uint8_t Length);

#endif
