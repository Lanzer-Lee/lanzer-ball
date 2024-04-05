#ifndef __DEBUG_H
#define __DEBUG_H

#include "stm32f10x.h"
#include "Serial.h"
#include "control.h"
#include "TIMER.h"
#include <string.h>
#include <stdio.h>

void debug_command_process(void);
void control_enable(void);

#endif
