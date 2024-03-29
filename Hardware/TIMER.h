#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "stm32f10x.h"
#include "control.h"
#include "motor.h"
#include "openmv.h"

void TIM_Init(void);
void TIM3_Int_Init(uint16_t arr,uint16_t psc);
void TIM2_Int_Init(uint16_t arr,uint16_t psc);

#endif
