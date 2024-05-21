#include "IIC.h"

/*
PE10->SCL
PE12->SDA
*/

void IIC_SDA_OUT(void){
    GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(CLOCK,ENABLE);
	GPIO_InitStructure.GPIO_Pin=IIC_IO_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOX,&GPIO_InitStructure); 						
}

void IIC_SDA_IN(void){
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(CLOCK,ENABLE);
	GPIO_InitStructure.GPIO_Pin=IIC_IO_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOX,&GPIO_InitStructure);
}

void IIC_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(CLOCK,ENABLE);	 
	GPIO_InitStructure.GPIO_Pin = IIC_IO_SDA|IIC_IO_SCL;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOX, &GPIO_InitStructure);			
	GPIO_SetBits(GPIOX,IIC_IO_SDA|IIC_IO_SCL); 
}

void IIC_Start(void){
	IIC_SDA_OUT();
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	Delay_us(5);
	IIC_SDA=0;
	Delay_us(5);
	IIC_SCL=0;
}

void IIC_Stop(void){
	IIC_SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
	Delay_us(5);
	IIC_SCL=1; 
	IIC_SDA=1;
	Delay_us(5);
}

//主机产生一个应答信号
void IIC_Ack(void){
    IIC_SCL=0;
	IIC_SDA_OUT();
    IIC_SDA=0;	
    Delay_us(2);
    IIC_SCL=1;
    Delay_us(2);
    IIC_SCL=0;	
}

//主机不产生应答信号
void IIC_NAck(void){
	IIC_SCL=0;
	IIC_SDA_OUT();
    IIC_SDA=1;
    Delay_us(2);
    IIC_SCL=1;
    Delay_us(2);
    IIC_SCL=0;
}

//等待从机应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
uint8_t IIC_Wait_Ack(void){
	uint8_t tempTime=0;
	IIC_SDA_IN();
	IIC_SDA=1;
	Delay_us(1);
	IIC_SCL=1;
	Delay_us(1);
	while(READ_SDA){
		tempTime++;
		if(tempTime>250){
			IIC_Stop();
			return 1;
		}	 
	}
	IIC_SCL=0;
	return 0;
}

void IIC_Send_Byte(uint8_t txd){
	uint8_t i=0;
	IIC_SDA_OUT();
	IIC_SCL=0;;//拉低时钟开始数据传输
	for(i=0;i<8;i++){
		IIC_SDA=(txd&0x80)>>7;//读取字节
		txd<<=1;
		Delay_us(2);
		IIC_SCL=1;
		Delay_us(2); //发送数据
		IIC_SCL=0;
		Delay_us(2);
	}
}

//读取一个字节
uint8_t IIC_Read_Byte(uint8_t ack){
	uint8_t i=0,receive=0;
	IIC_SDA_IN();
    for(i=0;i<8;i++){
   	    IIC_SCL=0;
		Delay_us(2);
		IIC_SCL=1;
		receive<<=1;//左移
		if(READ_SDA) receive++;//连续读取八位
		Delay_us(1);	
    }
    if(!ack) IIC_NAck();
	else IIC_Ack();
	return receive;//返回读取到的字节
}

uint8_t IIC_Read_Bytes(uint8_t address,uint8_t Reg,uint8_t *Buf,uint8_t Len){
	uint8_t i;
	IIC_Start();																				//发送起始信号
	IIC_Send_Byte((address << 1) | 0);	//发送元器件地址+写指令
	if(IIC_Wait_Ack() == 1){
		IIC_Stop();					
		return 1;					
	}
	IIC_Send_Byte(Reg);																	//发送寄存器地址
	if(IIC_Wait_Ack() == 1){
		IIC_Stop();
		return 1;
	}
	IIC_Start();																				//发送起始信号
	IIC_Send_Byte((address << 1) | 1);	//发送元器件地址+读指令
	if(IIC_Wait_Ack() == 1)															//等待响应，如果失败，发送停止信号，返回1
	{
		IIC_Stop();
		return 1;
	}
	for(i=0;i<Len;i++){	
		if(i != Len-1){																	
			Buf[i] = IIC_Read_Byte(1);										
		}
		else Buf[i] = IIC_Read_Byte(0);									
	}
	IIC_Stop();																					//发送停止信号
	return 0;																						//读取成功，返回0
}

//循环发送一个数组的数据（addr：地址  buf：数据内容  leng：数据长度）
uint8_t IIC_Send_Bytes(uint8_t address,uint8_t Reg,int8_t *Buf,uint8_t Len)//I2C的写数据
{
	uint8_t i;
	IIC_Start();																				//在起始信号后必须发送一个7位从机地址+1位方向位，用“0”表示主机发送数据，“1”表示主机接收数据。
	IIC_Send_Byte((address << 1) | 0);	//发送 器件地址+写的命令
	if(IIC_Wait_Ack() == 1){
		IIC_Stop();					
		return 1;					
	}
	IIC_Send_Byte(Reg);																	//发送 寄存器地址
	if(IIC_Wait_Ack() == 1){
		IIC_Stop();
		return 1;
	}
	for(i =0;i<Len;i++){
		IIC_Send_Byte(Buf[i]);														//发送第i位的8位数据
		if(IIC_Wait_Ack() == 1){
			IIC_Stop();
			return 1;
		}
	}
	IIC_Stop();																					//发送结束，发送停止信号
	return 0;																						//返回 0，确定发送成功
}
