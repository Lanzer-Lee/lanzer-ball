#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"
#include "debug.h"
#include "openmv.h"
#include "pid.h"
#include "echo.h"
#include "Expert.h"
#include "Fusion.h"

void TIM_Init(void);
void TIM2_Int_Init(uint16_t arr,uint16_t psc);
void TIM3_Int_Init(uint16_t arr,uint16_t psc);
void TIM4_Int_Init(uint16_t arr,uint16_t psc);

#endif
