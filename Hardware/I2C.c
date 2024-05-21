#include "I2C.h"
#if 1
void Delay(u32 count){
	unsigned int uiCnt = count*8;
	while (uiCnt --);
}

void I2C_IMU_Init(void){			
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	IMU_OUT();     
	I2C_SDA=1;	  	  
	I2C_SCL=1;
}

void I2C_Start(void){
	IMU_OUT();    
	I2C_SDA=1;	  	  
	I2C_SCL=1;
	
	Delay(5);
 	I2C_SDA=0;//START:when CLK is high,DATA change form high to low 
	
	Delay(5);
	I2C_SCL=0;
}
	  
void I2C_Stop(void)
{
	IMU_OUT();
	I2C_SCL=0;
	I2C_SDA=0;//STOP:when CLK is high DATA change form low to high
 	
	Delay(5);
	I2C_SCL=1; 
	I2C_SDA=1;
	
	Delay(5);							   	
}

u8 I2C_Wait_Ack(void)
{
	u8 ucErrTime=0; 
	IMU_IN();     
	I2C_SDA=1;
	Delay(5);	  
	while(IMU_READ_SDA){
		ucErrTime++;
		if(ucErrTime>50)
		{
			I2C_Stop();
			return 1;
		}
		Delay(5);
	}  
	I2C_SCL=1;
	Delay(5); 
	I2C_SCL=0;
	return 0;  
} 

void I2C_Ack(void){
	I2C_SCL=0;
	IMU_OUT();
	I2C_SDA=0;
	Delay(5);
	I2C_SCL=1;
	Delay(5);
	I2C_SCL=0;
}
	    
void I2C_NAck(void){
	I2C_SCL=0;
	IMU_OUT();
	I2C_SDA=1;
	Delay(5);
	I2C_SCL=1;
	Delay(5);
	I2C_SCL=0;
}					 				     
		  
void I2C_Send_Byte(u8 txd){                        
    u8 t; 
	IMU_OUT(); 	    
    I2C_SCL=0;
    for(t=0;t<8;t++){              
        I2C_SDA=(txd&0x80)>>7;
        txd<<=1; 	  	
		Delay(2);   
		I2C_SCL=1;
		Delay(5);
		I2C_SCL=0;	
		Delay(3);
    }	 
} 	 
  
u8 I2C_Read_Byte(unsigned char ack){
	unsigned char i,receive=0;
	IMU_IN();
    for(i=0;i<8;i++ ){
        I2C_SCL=0; 
		Delay(5);
		I2C_SCL=1;
        receive<<=1;
        if(IMU_READ_SDA)receive++;   
		Delay(5); 
    }					 
    if (ack)
        I2C_Ack(); 
    else
        I2C_NAck();
    return receive;
}

int32_t I2CreadBytes(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length){
    uint32_t count = 0;
    I2C_Start();
    I2C_Send_Byte(dev);	
    if(I2C_Wait_Ack() == 1)return 0;
    I2C_Send_Byte(reg);
    if(I2C_Wait_Ack() == 1)return 0;
    I2C_Start();
    I2C_Send_Byte(dev+1); 
    if(I2C_Wait_Ack() == 1)return 0;
    for(count=0; count<length; count++){
        if(count!=length-1)data[count]=I2C_Read_Byte(1);
        else  data[count]=I2C_Read_Byte(0);	 
    }
    I2C_Stop();
    return 1;
}


int32_t I2CwriteBytes(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length){
    uint32_t count = 0;
    I2C_Start();
    I2C_Send_Byte(dev);	   
    if(I2C_Wait_Ack() == 1)return 0;
    I2C_Send_Byte(reg);   
    if(I2C_Wait_Ack() == 1)return 0;
    for(count=0; count<length; count++){
        I2C_Send_Byte(data[count]);
        if(I2C_Wait_Ack() == 1)return 0;
    }
    I2C_Stop();
    return 1; 
}

#endif
