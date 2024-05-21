#ifndef __GAME_H
#define __GAME_H

#include "stm32f10x.h"
#include "series.h"
#include "valve.h"
#include "openmv.h"
#include "pid.h"
#include "echo.h"
#include "servo.h"
#include "Fusion.h"
#include "OLED.h"

#define PI      3.14159265358979f
#define LENGTH  23.5f
#define WIDTH   28.7f
#define HALF_WIDTH  14.35f
#define HALF_LENGTH 11.75f
#define RADIUS  4.50f
#define CAR_RADIUS  18.55f
#define PULSE_PER_CYCLE 3960
#define SPEED_10 7.70f
#define SPEED_20 15.60f
#define SPEED_30 23.30f
#define SPEED_40 31.50f
#define GAME_SPEED  20
#define PASS_POINT_X    290
#define PASS_POINT_Y    245
#define PASS_POINT_ANGLE    1.65
#define TACKLE_DISTANCE 20.0f
#define TACKLE_SPEED    10

#define GAME_ROUND0  0
#define GAME_ROUND1  1
#define GAME_ROUND2  2
#define GAME_ROUND3  3
#define GAME_ROUND4  4
#define GAME_ROUND5  5
#define GAME_ROUND6  6

#define GAME_STATE0  0
#define GAME_STATE1  1
#define GAME_STATE2  2
#define GAME_STATE3  3
#define GAME_STATE4  4
#define GAME_STATE5  5
#define GAME_STATE6  6
#define GAME_STATE7  7
#define GAME_STATE8  8
#define GAME_STATE9  9
#define GAME_STATE10  10
#define GAME_STATE11  11
#define GAME_STATE12  12
#define GAME_STATE13  13
#define GAME_STATE14  14
#define GAME_STATE15  15
#define GAME_STATE16  16

#define GAME_RIGHT  0
#define GAME_LEFT   1

#define GAME1_ANGLE_TIME    1999
#define GAME_LEAVE_BALL_TIME    500
#define GAME_WAIT_DETECT_TIME   1500
#define GAME_ANGLE90_TIME   1800

typedef struct{
    uint8_t Round;
    uint8_t State;
    uint8_t Direction;
}Game_TypeDef;

extern Game_TypeDef game;

void game_init(Game_TypeDef *Game);
void game_play(Game_TypeDef *Game);

#endif
