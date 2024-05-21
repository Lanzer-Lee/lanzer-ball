#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"
#include "GAME.h"
#include "OLED.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

void KEY_Init(void);
void EXTIX_Init(void);

#endif
