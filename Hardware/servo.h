#ifndef __SERVO_H
#define __SERVO_H

#include "Serial.h"

#define SERVO_NUM   2
#define SERVO_MOVE_TIME_WRITE   1
#define SERVO_MOVE_TIME_READ    2
#define SERVO_MOVE_TIME_WAIT_WRITE  7
#define SERVO_MOVE_TIME_WAIT_READ   8

#define UART_RX_ENABLE()		PAout(0) = 1;PAout(1) = 0
#define UART_TX_ENABLE()		PAout(0) = 0;PAout(1) = 1

extern char servo_cmd[];
extern uint16_t servo_time,servo_angle;
extern uint8_t servo_id;

void servo_init(void);
void servo_send_cmd(uint8_t id,uint16_t time, uint16_t angle);
void servo_data_process(void);

#endif
