#ifndef __POWER_H
#define __POWER_H

#include "stm32f10x.h"

void Power_Init(void);
void Power_Set(FunctionalState NewState);

#endif
