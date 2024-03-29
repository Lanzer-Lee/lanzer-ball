#include "Serial.h"

/*
USART1: PA9->TX, PA10->RX
USART2: PA2->TX, PA3->RX
USART3: PB10->TX, PB11->RX
*/

char Serial_RxPacket_USART1[100];				
uint8_t Serial_RxFlag_USART1;	
char Serial_RxPacket_USART2[100];				
uint8_t Serial_RxFlag_USART2;				

/* init function*/
void Serial_USART1_Init(int bound){
	/* communicate with computer */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					
	USART_InitTypeDef USART_InitStructure;				
	USART_InitStructure.USART_BaudRate = bound;				
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	
	USART_InitStructure.USART_Parity = USART_Parity_No;	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		
	USART_Init(USART1, &USART_InitStructure);				
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
	NVIC_InitTypeDef NVIC_InitStructure;					
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	NVIC_Init(&NVIC_InitStructure);							
	USART_Cmd(USART1, ENABLE);							
}

void Serial_USART2_Init(int bound){
	/* communicate with openmv */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	USART_InitTypeDef USART_InitStructure;				
	USART_InitStructure.USART_BaudRate = bound;			
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	
	USART_InitStructure.USART_Parity = USART_Parity_No;		
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		
	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);			
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
	NVIC_InitTypeDef NVIC_InitStructure;					
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	NVIC_Init(&NVIC_InitStructure);	
	USART_Cmd(USART2, ENABLE);
}

void Serial_USART3_Init(int bound){
	/* communicate with motor control board */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);				
	USART_InitTypeDef USART_InitStructure;				
	USART_InitStructure.USART_BaudRate = bound;			
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	
	USART_InitStructure.USART_Parity = USART_Parity_No;		
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		
	USART_Init(USART3, &USART_InitStructure);				
	USART_Cmd(USART3, ENABLE);								
}

void Serial_USARTx_Init(void){
	Serial_USART1_Init(115200);
	Serial_USART2_Init(115200);
	Serial_USART3_Init(115200);
	
}

/* universal function */
uint32_t Serial_Pow(uint32_t X, uint32_t Y){
	uint32_t Result = 1;	
	while (Y --){
		Result *= X;	
	}
	return Result;
}

void Serial_SendByte(USART_TypeDef* USARTx,uint8_t Byte){
	USART_SendData(USARTx, Byte);		
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
}

void Serial_SendString(USART_TypeDef* USARTx,char *String){
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++){
		Serial_SendByte(USARTx,String[i]);	
	}
}

void Serial_SendArray(USART_TypeDef* USARTx,uint8_t *Array, uint16_t Length){
	uint16_t i;
	for (i = 0; i < Length; i ++){
		Serial_SendByte(USARTx,Array[i]);	
	}
}

void Serial_SendNumber(USART_TypeDef* USARTx,uint32_t Number, uint8_t Length){
	uint8_t i;
	for (i = 0; i < Length; i ++){
		Serial_SendByte(USARTx,Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/*USART1 function*/
void Serial_USART1_SendByte(uint8_t Byte){
	USART_SendData(USART1, Byte);		
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
}

void Serial_USART1_SendString(char *String){
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++){
		Serial_USART1_SendByte(String[i]);		
	}
}

void Serial_USART1_SendArray(uint8_t *Array, uint16_t Length){
	uint16_t i;
	for (i = 0; i < Length; i ++){
		Serial_USART1_SendByte(Array[i]);	
	}
}

void Serial_USART1_SendNumber(uint32_t Number, uint8_t Length){
	uint8_t i;
	for (i = 0; i < Length; i ++){
		Serial_USART1_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/*USART2 function*/
void Serial_USART2_SendByte(uint8_t Byte){
	USART_SendData(USART2, Byte);		
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	
}

void Serial_USART2_SendString(char *String){
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++){
		Serial_USART2_SendByte(String[i]);		
	}
}

void Serial_USART2_SendArray(uint8_t *Array, uint16_t Length){
	uint16_t i;
	for (i = 0; i < Length; i ++){
		Serial_USART2_SendByte(Array[i]);	
	}
}

void Serial_USART2_SendNumber(uint32_t Number, uint8_t Length){
	uint8_t i;
	for (i = 0; i < Length; i ++){
		Serial_USART2_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/*USART3 function*/
void Serial_USART3_SendByte(uint8_t Byte){
	USART_SendData(USART3, Byte);		
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	
}

void Serial_USART3_SendString(char *String){
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++){
		Serial_USART3_SendByte(String[i]);	
	}
}

void Serial_USART3_SendArray(uint8_t *Array, uint16_t Length){
	uint16_t i;
	for (i = 0; i < Length; i ++){
		Serial_USART3_SendByte(Array[i]);	
	}
}

void Serial_USART3_SendNumber(uint32_t Number, uint8_t Length){
	uint8_t i;
	for (i = 0; i < Length; i ++){
		Serial_USART3_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/* USART1 by printf */
int fputc(int ch, FILE *f){
	Serial_USART1_SendByte(ch);			
	return ch;
}

void Serial_Printf(char *format, ...){
	char String[100];				
	va_list arg;					
	va_start(arg, format);			
	vsprintf(String, format, arg);	
	va_end(arg);					
	Serial_USART1_SendString(String);		
}

/* interuption function*/
void USART1_IRQHandler(void){
	static uint8_t RxState = 0;		
	static uint8_t pRxPacket = 0;	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET){
		uint8_t RxData = USART_ReceiveData(USART1);			
		if (RxState == 0){
			if (Serial_RxFlag_USART1 == 0  && (RxData == SERVO_FLAG || RxData==MOTOR_FLAG ||RxData=='$')){
				RxState = 1;			
				pRxPacket = 0;
				Serial_RxPacket_USART1[pRxPacket] = RxData;
				pRxPacket ++;		
			}
			if (Serial_RxFlag_USART1 == 0  && RxData=='*'){		
				pRxPacket = 0;
				Serial_RxPacket_USART1[pRxPacket] = RxData;
				pRxPacket ++;	
				Serial_RxPacket_USART1[pRxPacket] ='\0';
				Serial_RxFlag_USART1 = 1;	
			}
		}
		else if (RxState == 1){
			if (RxData == END_FLAG){
				RxState = 0;
				Serial_RxPacket_USART1[pRxPacket] = RxData;
				pRxPacket ++;		
				Serial_RxPacket_USART1[pRxPacket] = '\0';
				Serial_RxFlag_USART1 = 1;
			}
			else{
				Serial_RxPacket_USART1[pRxPacket] = RxData;		
				pRxPacket ++;			
			}
		}	
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		
	}
}

void USART2_IRQHandler(void){
	static uint8_t RxState = 0;		
	static uint8_t pRxPacket = 0;	
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET){
		uint8_t RxData = USART_ReceiveData(USART2);			
		if (RxState == 0){
			if (Serial_RxFlag_USART2 == 0  && RxData=='('){
				RxState = 1;			
				pRxPacket = 0;
				Serial_RxPacket_USART2[pRxPacket] = RxData;
				pRxPacket ++;		
			}
		}
		else if (RxState == 1){
			if (RxData == ')'){
				RxState = 0;
				Serial_RxPacket_USART2[pRxPacket] = RxData;
				pRxPacket ++;		
				Serial_RxPacket_USART2[pRxPacket] = '\0';
				Serial_RxFlag_USART2 = 1;
			}
			else{
				Serial_RxPacket_USART2[pRxPacket] = RxData;		
				pRxPacket ++;			
			}
		}	
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);		
	}
}
