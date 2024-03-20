#include "control.h"

uint8_t aim_ball_mid(void){
    if(0<=target_x && target_x<157){
        standard_left(100,100);
        return NOTMID;
    }
    if(target_x>163){
        standard_right(100,100);
        return NOTMID;
    }
    if(157<=target_x && target_x<=163){
        return MID;
    }
    return NOTMID;
}

uint8_t find_ball_mid(void){
    standard_clockwise(100,100);
    if(target_x>=0){
        return MID;
    }
    return NOTMID;
}
