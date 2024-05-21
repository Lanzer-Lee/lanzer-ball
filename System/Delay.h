#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

#define ATK_DELAY   1

#if ATK_DELAY
void Delay_Init(void);
void Delay_us(uint32_t nus);
void Delay_ms(uint16_t nms);

#else 
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);
#endif

#endif
