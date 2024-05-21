#include "debug.h"

Debug_TypeDef data;

void debug_init(Debug_TypeDef *Data){
    uint8_t i=0;
    Data->Identifier=0;
    for(i=0;i<INTEGER_NUM;i++) Data->Data_int[i]=0;
    for(i=0;i<FLOAT_NUM;i++) Data->Data_float[i]=0.0;
}

void debug_analysis(Debug_TypeDef *Data){
    if(Serial_RxFlag_USART1==1){
        switch (Serial_RxPacket_USART1[1]){
            case GAME_DEBUG:
                game.Round=Serial_RxPacket_USART1[2]-'0';
                game.State=GAME_STATE0;
                break;
            case MOTOR_DENUG:
                sscanf(Serial_RxPacket_USART1,"(M,%d,%d,%d,%d)",&Data->Data_int[0],&Data->Data_int[1],&Data->Data_int[2],&Data->Data_int[3]);
                Motor_SetVelocity(&motor,(int8_t)(Data->Data_int[0]),(int8_t)(Data->Data_int[1]),(int8_t)(Data->Data_int[2]),(int8_t)(Data->Data_int[3]));
                break;
            case ATTITUDE_DEBUG:
                attitude_algorithm(&robot);
                printf("x=%.1f,y=%.1f,angle=%.1f\r\n",robot.x,robot.y,robot.angle);
                printf("encoder=%d,%d,%d,%d\r\n",motor.Encoder[0],motor.Encoder[1],motor.Encoder[2],motor.Encoder[3]);
                Motor_ReadVoltage(&motor);
                printf("voltage=%d\r\n",motor.Voltage);
                break;
            case SERIES_DEBUG:
                sscanf(Serial_RxPacket_USART1,"(C,%f,%d,%d)",&Data->Data_float[0],&Data->Data_int[0],&Data->Data_int[1]);
                series_set(&series,Data->Data_float[0],(uint8_t)(Data->Data_int[0]),(uint8_t)(Data->Data_int[1]));
                series_control(&series);
                break;
            case VALVE_DUBUG:
                sscanf(Serial_RxPacket_USART1,"(V,%d)",&Data->Data_int[0]);
                valve_hit((uint16_t)(Data->Data_int[0]));
                break;
            case TOF_DEBUG:
                //TOF_GetData(&tof);
                printf("d=%.1f,e=%d,n=%d\r\n",tof.Distance,tof.Energy,tof.Noise);
                break;
            case OPENMV_DEBUG:
                sscanf(Serial_RxPacket_USART1,"(O,%d)",&Data->Data_int[0]);
                openmv_set(&cv,(uint8_t)(Data->Data_int[0]));
                printf("x=%.1f,y=%.1f,d=%.1f,k=%.1f\r\n",cv.X,cv.Y,cv.Distance,cv.Slope);
                break;
            case SERVO_DEBUG:
                sscanf(Serial_RxPacket_USART1,"(S,%d,%d,%d)",&Data->Data_int[0],&Data->Data_int[1],&Data->Data_int[2]);
                servo.ID=(uint8_t)(Data->Data_int[0]);
                servo.Angle=(uint16_t)(Data->Data_int[1]);
                servo.Time=(uint16_t)(Data->Data_int[2]);
                servo_control(&servo);
                break;
            case PID_DEBUG:
                sscanf(Serial_RxPacket_USART1,"(P,%f,%f,%f,%f,%d)",&Data->Data_float[0],&Data->Data_float[1],&Data->Data_float[2],&Data->Data_float[3],&Data->Data_int[0]);
                pid_set_parameter(&pid,Data->Data_float[0],Data->Data_float[1],Data->Data_float[2]);
                pid_set(&pid,Data->Data_float[3],(uint8_t)(Data->Data_int[0]));
                pid_enable(&pid);
                break;
            case FUSION_DEBUG:
                sscanf(Serial_RxPacket_USART1,"(F,%d,%d,%d,%d)",&Data->Data_int[0],&Data->Data_int[1],&Data->Data_int[2],&Data->Data_int[3]);
                Fusion_Set(&fusion,(uint16_t)(Data->Data_int[0]),(uint16_t)(Data->Data_int[1]),(uint8_t)(Data->Data_int[2]),(int8_t)(Data->Data_int[3]));
                printf("fusion set:%d,%d\r\n",fusion.LowerBound,fusion.UpperBound);
                Fusion_FindBall(&fusion);
                break;
            case IMU_DEBUG:
                IMU_Data_Process(&imu);
                printf("azimuth=%.3f\r\n",imu.Azimuth);
                printf("angle=%.1f,%.1f,%.1f\r\n",imu.Angle[0],imu.Angle[1],imu.Angle[2]);
                break;
            case ECHO_DEBUG:
                echo_diatance=echo_measure_distance();
                printf("echo=%.2f",echo_diatance);
                break;
            case POWER_DEBUG:
                sscanf(Serial_RxPacket_USART1,"(Q,%d)",&Data->Data_int[0]);
                if(Data->Data_int[0]==0) Power_Set(DISABLE);
                else Power_Set(ENABLE);
                break;
            default:break;
        }
        printf(Serial_RxPacket_USART1);
        printf("\r\n");
        Serial_RxFlag_USART1=0;
    }
}
