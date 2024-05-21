#include "motor.h"

Motor_TypeDef motor;

void Motor_Init(Motor_TypeDef *Motor){
    /*hardware init*/
    int8_t motor_type=MOTOR_TYPE_JGB37;
    int8_t motor_encoder_polarity=0;
    Delay_ms(200);
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_TYPE_JGB37,&motor_type,4);
    Delay_ms(5);
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_ENCODER_POLARITY_ADDR,&motor_encoder_polarity,1);
    Delay_ms(5);
    /*software init*/
    uint8_t i=0;
    Motor->Voltage=0;
    for(i=0;i<3;i++) Motor->VoltageBuffer[i]=0;
    for(i=0;i<MOTOR_NUM;i++){
        Motor->PrevEncoder[i]=0;
        Motor->LastEncoder[i]=0;
        Motor->Encoder[i]=0;
        Motor->Velocity[i]=0;
    }
}

void Motor_ReadVoltage(Motor_TypeDef *Motor){
    IIC_Read_Bytes(CAM_I2C_ADDRESS,ADC_BAT_ADDR,Motor->VoltageBuffer,2);
    Motor->Voltage=Motor->VoltageBuffer[0]+(Motor->VoltageBuffer[1]<<8);
}

uint8_t Motor_ReadEncoderCorrection(Motor_TypeDef *Motor){
    uint8_t i=0;
    /*update*/
    
    for(i=0;i<MOTOR_NUM;i++){
        Motor->PrevEncoder[i]=Motor->LastEncoder[i];
        Motor->LastEncoder[i]=Motor->Encoder[i];
    }
    
    IIC_Read_Bytes(CAM_I2C_ADDRESS,MOTOR_ENCODER_TOTAL_ADDR,(uint8_t *)Motor->Encoder,16);
    /*correction*/
    
    int32_t DeltaEncoder[MOTOR_NUM]={0};
    int32_t AverageEncoder=0;
    for(i=0;i<MOTOR_NUM;i++) DeltaEncoder[i]=Motor->Encoder[i]-Motor->LastEncoder[i];
    if(Motor->Encoder[1]==-1 && Motor->Encoder[2]==-1 && Motor->Encoder[3]==-1){
        Motor_Encoder_Revise(Motor);
        printf("MOTOR ERROR7\r\n");
        return 2;
    }
    else if(DeltaEncoder[0]>=0 && DeltaEncoder[1]>=0 && DeltaEncoder[2]>=0 && DeltaEncoder[3]>=0){
        AverageEncoder=(DeltaEncoder[0]+DeltaEncoder[1]+DeltaEncoder[2]+DeltaEncoder[3])/4;
        for(i=0;i<MOTOR_NUM;i++){
            if(abs(DeltaEncoder[i]-AverageEncoder)>MOTOR_ENCODER_ERROR){
                Motor_Encoder_Revise(Motor);
                printf("MOTOR ERROR0\r\n");
                return 1;
            }
            else return 0;
        }
    }
    else if(DeltaEncoder[0]<=0 && DeltaEncoder[1]<=0 && DeltaEncoder[2]<=0 && DeltaEncoder[3]<=0){
        AverageEncoder=(DeltaEncoder[0]+DeltaEncoder[1]+DeltaEncoder[2]+DeltaEncoder[3])/4;
        for(i=0;i<MOTOR_NUM;i++){
            if(abs(DeltaEncoder[i]-AverageEncoder)>MOTOR_ENCODER_ERROR){
                Motor_Encoder_Revise(Motor);
                printf("MOTOR ERROR1\r\n");
                return 1;
            }
            else return 0;
        }
    }
    else if(DeltaEncoder[0]<=0 && DeltaEncoder[1]>=0 && DeltaEncoder[2]>=0 && DeltaEncoder[3]<=0){
        AverageEncoder=(DeltaEncoder[0]+DeltaEncoder[1]+DeltaEncoder[2]+DeltaEncoder[3])/4;
        if(AverageEncoder>MOTOR_ENCODER_ERROR/4){
            Motor_Encoder_Revise(Motor);
            printf("MOTOR ERROR2\r\n");
            return 1;
        }
        else return 0;
    }
    else if(DeltaEncoder[0]>=0 && DeltaEncoder[1]<=0 && DeltaEncoder[2]<=0 && DeltaEncoder[3]>=0){
        AverageEncoder=(DeltaEncoder[0]+DeltaEncoder[1]+DeltaEncoder[2]+DeltaEncoder[3])/4;
        if(AverageEncoder>MOTOR_ENCODER_ERROR/4){
            Motor_Encoder_Revise(Motor);
            printf("MOTOR ERROR3\r\n");
            return 1;
        }
        else return 0;
    }
    else if(DeltaEncoder[0]>=0 && DeltaEncoder[1]>=0 && DeltaEncoder[2]<=0 && DeltaEncoder[3]<=0){
        AverageEncoder=(DeltaEncoder[0]+DeltaEncoder[1]+DeltaEncoder[2]+DeltaEncoder[3])/4;
        if(AverageEncoder>MOTOR_ENCODER_ERROR/4){
            Motor_Encoder_Revise(Motor);
            printf("MOTOR ERROR4\r\n");
            return 1;
        } 
        else return 0;
    }
    else if(DeltaEncoder[0]<=0 && DeltaEncoder[1]<=0 && DeltaEncoder[2]>=0 && DeltaEncoder[3]>=0){
        AverageEncoder=(DeltaEncoder[0]+DeltaEncoder[1]+DeltaEncoder[2]+DeltaEncoder[3])/4;
        if(AverageEncoder>MOTOR_ENCODER_ERROR/4){
            Motor_Encoder_Revise(Motor);
            printf("MOTOR ERROR5\r\n");
            return 1;
        }
        else return 0;
    }
    printf("MOTOR ERROR6\r\n");
    return 1;
    
}

void Motor_ReadEncoder(Motor_TypeDef *Motor){
    uint8_t flag=Motor_ReadEncoderCorrection(Motor);
    uint8_t i=0;
    for(i=0;i<5&&flag==1;i++){
        Delay_us(100);
        flag=Motor_ReadEncoderCorrection(Motor);

    }
    if(flag){
        Power_Set(DISABLE);
        Delay_ms(1000);
        Power_Set(ENABLE);
        Delay_ms(1);
        Motor_Init(&motor);
        Delay_ms(500);
    }
}

void Motor_Encoder_Revise(Motor_TypeDef *Motor){
    uint8_t i=0;
    for(i=0;i<MOTOR_NUM;i++){
        Motor->Encoder[i]=Motor->LastEncoder[i];
        Motor->LastEncoder[i]=Motor->PrevEncoder[i];
    }
}

void Motor_SetVelocity(Motor_TypeDef *Motor,int8_t V_lf,int8_t V_rf,int8_t V_lb,int8_t V_rb){
    Motor->Velocity[0]=V_lf;
    Motor->Velocity[1]=V_rf;
    Motor->Velocity[2]=V_lb;
    Motor->Velocity[3]=V_rb;
    IIC_Send_Bytes(CAM_I2C_ADDRESS,MOTOR_FIXED_SPEED_ADDR,Motor->Velocity,4);
    //Delay_us(50);
}

void Motor_Straight(int8_t velocity){
    if(velocity>0) Motor_SetVelocity(&motor,velocity,velocity,velocity,velocity);
    else Motor_SetVelocity(&motor,velocity,velocity,velocity,velocity);
}

void Motor_Horizontal(int8_t velocity){
    if(velocity>0) Motor_SetVelocity(&motor,-velocity-1,velocity,velocity+1,-velocity);
    else Motor_SetVelocity(&motor,-velocity,velocity-1,velocity-1,-velocity);
}

void Motor_Rote(int8_t velocity){
    Motor_SetVelocity(&motor,velocity,-velocity,velocity,-velocity);
}

void Motor_Stop(Motor_TypeDef *Motor){
    Motor_SetVelocity(Motor,0,0,0,0);
    //motor_read_encoder();
    //attitude_algorithm(&robot);
    //printf("x=%.1f,y=%.1f\r\n",robot.x,robot.y);
}
