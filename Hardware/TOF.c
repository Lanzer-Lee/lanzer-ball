#include "TOF.h"

TOF_TypeDef tof;

uint8_t TOF_CountSum(uint8_t *buf){
    uint8_t len=0,checksum=0;
    len=sizeof(buf)+1;
    while(len--){
        checksum+=*buf;
        buf++;
    }
    checksum&=0xFF;
    return checksum;
}

void TOF_Init(TOF_TypeDef *TOF){
    TOF->Distance=65535.0;
    TOF->Energy=0;
    TOF->Noise=0;
    TOF_SetStandard(TOF);
    TOF_Start(TOF);
}

void TOF_Stop(TOF_TypeDef *TOF){
    TOF->SendBuffer[0]=0xAA;
    TOF->SendBuffer[1]=0x55;
    TOF->SendBuffer[2]=0x61;
    TOF->SendBuffer[3]=0x00;
    TOF->SendBuffer[4]=0x60;
    Serial_SendArray(UART4,TOF->SendBuffer,5);
    memset(TOF->SendBuffer,0,sizeof(TOF->SendBuffer));
}

void TOF_Start(TOF_TypeDef *TOF){
    TOF->SendBuffer[0]=0xAA;
    TOF->SendBuffer[1]=0x55;
    TOF->SendBuffer[2]=0x60;
    TOF->SendBuffer[3]=0x00;
    TOF->SendBuffer[4]=0x5F;
    Serial_SendArray(UART4,TOF->SendBuffer,5);
    memset(TOF->SendBuffer,0,sizeof(TOF->SendBuffer));
}

void TOF_SetStandard(TOF_TypeDef *TOF){
    TOF->SendBuffer[0]=0xAA;
    TOF->SendBuffer[1]=0x55;
    TOF->SendBuffer[2]=0x67;
    TOF->SendBuffer[3]=0x01;
    TOF->SendBuffer[4]=0x00;
    TOF->SendBuffer[5]=0x67;
    Serial_SendArray(UART4,TOF->SendBuffer,6);
    memset(TOF->SendBuffer,0,sizeof(TOF->SendBuffer));
}

void TOF_SetBaudrate(TOF_TypeDef *TOF,uint8_t TOF_BAUD){
    TOF->SendBuffer[0]=0xAA;
    TOF->SendBuffer[1]=0x55;
    TOF->SendBuffer[2]=0x66;
    TOF->SendBuffer[3]=0x01;
    TOF->SendBuffer[4]=TOF_BAUD;
    TOF->SendBuffer[5]=TOF_CountSum(TOF->SendBuffer);
    Serial_SendArray(UART4,TOF->SendBuffer,6);
    memset(TOF->SendBuffer,0,sizeof(TOF->SendBuffer));
}

void TOF_SetFrequency(TOF_TypeDef *TOF,uint8_t TOF_FREQ){
    TOF->SendBuffer[0]=0xAA;
    TOF->SendBuffer[1]=0x55;
    TOF->SendBuffer[2]=0x64;
    TOF->SendBuffer[3]=0x01;
    TOF->SendBuffer[4]=TOF_FREQ;
    TOF->SendBuffer[5]=TOF_CountSum(TOF->SendBuffer);
    Serial_SendArray(UART4,TOF->SendBuffer,6);
    memset(TOF->SendBuffer,0,sizeof(TOF->SendBuffer));
}

void TOF_Decode(TOF_TypeDef *TOF,uint8_t RxData){
    static uint8_t RecCmd_Step=0,Checksum=0,RecCmd_Data_len=0,Data_cnt=0;
    switch(RecCmd_Step){
		case 0:
		if(RxData == 0xAA){
			TOF->RxBufferTemp[0]=RxData;
			RecCmd_Step++;
		}
		Checksum = 0xAA;
		break;
		
		case 1:
		if(RxData == 0x55){
			TOF->RxBufferTemp[1]=RxData;
			RecCmd_Step++;
			Data_cnt = 0;
			Checksum+=RxData;
			RecCmd_Data_len = 0;
		}
		else{
			RecCmd_Step = 0;
		}
		break;
		
		case 2:
			TOF->RxBufferTemp[2]=RxData;
			Checksum+=RxData;
			RecCmd_Step++;
		break;
		
		case 3:
			TOF->RxBufferTemp[3]=RxData;
			Checksum+=RxData;
			RecCmd_Data_len = TOF->RxBufferTemp[3];
			RecCmd_Step = RecCmd_Data_len==0 ? 5 : RecCmd_Step+1; 
		break;
		
		case 4:
		if(Data_cnt<RecCmd_Data_len){
			TOF->RxBufferTemp[4+Data_cnt++]=RxData;
			Checksum+=RxData;
			if(Data_cnt>=RecCmd_Data_len){
			RecCmd_Step++;
			}
		}
		break;
		
		case 5:
		if(Checksum==RxData){
			memcpy(TOF->SensorData,&TOF->RxBufferTemp[0],18); 
			memset(TOF->RxBufferTemp,0,18);//清一下数据
			RecCmd_Step=0;
			Data_cnt = 0;
			Checksum = 0;
		}
		else{
			RecCmd_Step = 0;
			Data_cnt = 0;
			Checksum = 0;
			memset(TOF->RxBufferTemp,0,18);//清一下数据
		}
		break;
		
		default: break;
	}
}

uint8_t TOF_GetData(TOF_TypeDef *TOF){
    if(TOF->SensorData[0]=='\0') return 0;
    if(TOF->SensorData[3]==0x00){
        memset(TOF->SensorData,0,18);
        return 0;
    }
    TOF->Distance=(float)(TOF->SensorData[5]<<8|TOF->SensorData[4]);
    if(TOF->Distance<0.01) TOF->Distance=65535;
    TOF->Energy=TOF->SensorData[6];
    TOF->Noise=TOF->SensorData[7];
    memset(TOF->SensorData,0,18);
    return 1;
}

uint8_t TOF_Scan(TOF_TypeDef *TOF,uint16_t lower_bound,uint16_t upper_bound){
    TOF_GetData(TOF);
    if(lower_bound<TOF->Distance&&TOF->Distance<upper_bound) return 1;
    else if(TOF->Distance<lower_bound) return 2;
    return 0;
}

void TOF_Find_Ball(TOF_TypeDef *TOF,uint8_t direction){
    if(direction==OPENMV_SEARCH_LEFT){
        Motor_Horizontal(-GAME_SPEED);
    }
    else if(direction==OPENMV_SEARCH_RIGHT){
        Motor_Horizontal(GAME_SPEED);
    }
    uint8_t flag=TOF_Scan(TOF,TOF_NEAR_BOUND,TOF_FAR_BOUND);
    while(!flag){
        flag=TOF_Scan(TOF,TOF_NEAR_BOUND,TOF_FAR_BOUND);
    }
    Motor_Stop(&motor);
}

void TOF_Aim_Ball(TOF_TypeDef *TOF){
    TOF_GetData(TOF);
    if(TOF->Distance>TOF_LIFT_DISTANCE) Motor_Straight(10);
    while(TOF->Distance>TOF_LIFT_DISTANCE){
        TOF_GetData(TOF);
    }
    Motor_Stop(&motor);
    Delay_ms(5);
    Motor_Stop(&motor);
}




