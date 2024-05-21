#include "attitude.h"

Robot_TypeDef robot;

void attitude_init(Robot_TypeDef *Robot){
    uint8_t i=0;
    for(i=0;i<5;i++){
        Robot->old_mileage[i]=0.0;
        Robot->pre_mileage[i]=0.0;
        Robot->diff_mileage[i]=0.0;
        Robot->old_encoder[i]=0;
        Robot->pre_encoder[i]=0;
        Robot->diff_encoder[i]=0;
    }
    Robot->x=0.0;
    Robot->y=0.0;
    Robot->angle=0.0;
}

void attitude_algorithm(Robot_TypeDef *Robot){
    uint8_t i=0;
    Motor_ReadEncoder(&motor);
    /*update*/
    for(i=0;i<5;i++){Robot->old_encoder[i]=Robot->pre_encoder[i];}
    for(i=1;i<5;i++){Robot->pre_encoder[i]=motor.Encoder[i-1];}
    for(i=1;i<5;i++){Robot->diff_encoder[i]=Robot->pre_encoder[i]-Robot->old_encoder[i];}
    /*attitude*/
    if(Robot->diff_encoder[1]>=0 && Robot->diff_encoder[2]>=0 && Robot->diff_encoder[3]>=0 && Robot->diff_encoder[4]>=0){
        /*straight forward move*/
        Robot->diff_encoder[0]=(Robot->diff_encoder[1]+Robot->diff_encoder[2]+Robot->diff_encoder[3]+Robot->diff_encoder[4])/4;
        Robot->x+=(float)(Robot->diff_encoder[0])/(float)(PULSE_PER_CYCLE)*2.0*PI*RADIUS;
    }
    else if(Robot->diff_encoder[1]<0 && Robot->diff_encoder[2]<0 && Robot->diff_encoder[3]<0 && Robot->diff_encoder[4]<0){
        /*straight backward move*/
        Robot->diff_encoder[0]=(-Robot->diff_encoder[1]-Robot->diff_encoder[2]-Robot->diff_encoder[3]-Robot->diff_encoder[4])/4;
        Robot->x-=(float)(Robot->diff_encoder[0])/(float)(PULSE_PER_CYCLE)*2.0*PI*RADIUS;
    }
    else if(Robot->diff_encoder[1]>=0 && Robot->diff_encoder[2]<0 && Robot->diff_encoder[3]<0 && Robot->diff_encoder[4]>=0){
        /*horizontal left move*/
        Robot->diff_encoder[0]=(Robot->diff_encoder[1]-Robot->diff_encoder[2]-Robot->diff_encoder[3]+Robot->diff_encoder[4])/4;
        Robot->y-=(float)(Robot->diff_encoder[0])/(float)(PULSE_PER_CYCLE)*2.0*PI*RADIUS;
    }
    else if(Robot->diff_encoder[1]<0 && Robot->diff_encoder[2]>=0 && Robot->diff_encoder[3]>=0 && Robot->diff_encoder[4]<0){
        /*horizontal right move*/
        Robot->diff_encoder[0]=(-Robot->diff_encoder[1]+Robot->diff_encoder[2]+Robot->diff_encoder[3]-Robot->diff_encoder[4])/4;
        Robot->y+=(float)(Robot->diff_encoder[0])/(float)(PULSE_PER_CYCLE)*2.0*PI*RADIUS;
    }
    else if(Robot->diff_encoder[1]>=0 && Robot->diff_encoder[2]<0 && Robot->diff_encoder[3]>=0 && Robot->diff_encoder[4]<0){
        /*clockwise*/
        Robot->diff_encoder[0]=(Robot->diff_encoder[1]-Robot->diff_encoder[2]+Robot->diff_encoder[3]-Robot->diff_encoder[4])/4;
        Robot->angle+=(float)(Robot->diff_encoder[0])/(float)(PULSE_PER_CYCLE)*2.0*PI*RADIUS/(HALF_LENGTH+HALF_WIDTH);
    }
    else if(Robot->diff_encoder[1]<0 && Robot->diff_encoder[2]>=0 && Robot->diff_encoder[3]<0 && Robot->diff_encoder[4]>=0){
        /*anti-clockwise*/
        Robot->diff_encoder[0]=(-Robot->diff_encoder[1]+Robot->diff_encoder[2]-Robot->diff_encoder[3]+Robot->diff_encoder[4])/4;
        Robot->angle-=(float)(Robot->diff_encoder[0])/(float)(PULSE_PER_CYCLE)*2.0*PI*RADIUS/(HALF_LENGTH+HALF_WIDTH);
    }
    else return;
    Robot->pre_encoder[0]+=Robot->diff_encoder[0];
    //printf("diff_encoder=%d,%d,%d,%d,%d\r\n",Robot->diff_encoder[0],Robot->diff_encoder[1],Robot->diff_encoder[2],Robot->diff_encoder[3],Robot->diff_encoder[4]);
}

