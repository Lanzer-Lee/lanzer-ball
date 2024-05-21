#include "series.h"

Series_TypeDef series;

void series_init(Series_TypeDef *Series){
    Series->SetPoint=0.0;
    Series->Error=0.0;
    Series->pFeedbackValue=NULL;
    Series->Mode=MODE_STRAIGHT;
    Series->Speed=20;
}

void series_set(Series_TypeDef *Series,float target,uint8_t speed,uint8_t mode){
    Series->SetPoint=target;
    Series->Error=0.0;
    Series->Speed=speed;
    Series->Mode=mode;
    switch (mode){
        case MODE_STRAIGHT:Series->pFeedbackValue=&robot.x;break;
        case MODE_HORIZONTAL:Series->pFeedbackValue=&robot.y;break;
        case MODE_ROTE:Series->pFeedbackValue=&robot.angle;break;
        default: break;
    }
}

uint8_t series_move(float displacement,int8_t velocity,uint8_t mode){
    float time=0.0,speed=0.0;
    switch (velocity){
        case 10:speed=SPEED_10;break;
        case 20:speed=SPEED_20;break;
        case 30:speed=SPEED_30;break;
        default:break;
    }
    if(displacement>=0){
        switch (mode){
            case MODE_STRAIGHT:
                time=displacement/speed*1000;
                if(time<100){Motor_Stop(&motor);return 1;}
                Motor_Straight(velocity);
                break;
            case MODE_HORIZONTAL:
                time=displacement/speed*1000;
                if(time<100){Motor_Stop(&motor);return 1;}
                Motor_Horizontal(velocity);
                break;
            case MODE_ROTE:
                time=displacement*(HALF_LENGTH+HALF_WIDTH)/speed*1000;
                if(time<100){Motor_Stop(&motor);return 1;}
                Motor_Rote(velocity);
                break;
            default:break;
        }
    }
    else{
        switch (mode){
            case MODE_STRAIGHT:
                time=-displacement/speed*1000;
                if(time<100){Motor_Stop(&motor);return 1;}
                Motor_Straight(-velocity);
                break;
            case MODE_HORIZONTAL:
                time=-displacement/speed*1000;
                if(time<100){Motor_Stop(&motor);return 1;}
                Motor_Horizontal(-velocity);
                break;
            case MODE_ROTE:
                time=-displacement*(HALF_LENGTH+HALF_WIDTH)/speed*1000;
                if(time<100){Motor_Stop(&motor);return 1;}
                Motor_Rote(-velocity);
                break;
            default:break;
        }
    }
    Delay_ms((uint16_t)(time));
    Motor_Stop(&motor);
    printf("series time=%d\r\n",(uint16_t)(time));   
    printf("encoder=%d,%d,%d,%d\r\n",motor.Encoder[0],motor.Encoder[1],motor.Encoder[2],motor.Encoder[3]);
    return 0;
}

void series_control(Series_TypeDef *Series){
    attitude_algorithm(&robot);
    Series->Error=Series->SetPoint-*(Series->pFeedbackValue);
    uint8_t flag=series_move(Series->Error,Series->Speed,Series->Mode);
    while (!flag){
        Series->Error=Series->SetPoint-*(Series->pFeedbackValue);
        flag=series_move(Series->Error,20,Series->Mode);
    }
    Delay_ms(5);
    Motor_Stop(&motor);
    if(Series->SetPoint<0.01 && Series->Mode==MODE_ROTE) robot.angle=0.0f;
}
