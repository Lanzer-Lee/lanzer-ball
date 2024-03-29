#include "IIC.h"

void IIC_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_2);
}

void IIC_Start(void){
    SDA_OUT();
    IIC_SDA=1;
    IIC_SCL=1;
    Delay_us(4);
    IIC_SDA=0;
    Delay_us(4);
    IIC_SCL=0;
}

void IIC_Stop(void){
    SDA_OUT();
    IIC_SCL=0;
    IIC_SDA=0;
    Delay_us(4);
    IIC_SCL=1;
    IIC_SDA=1;
    Delay_us(4);
}

uint8_t IIC_Wait_Ack(void){
    uint8_t ucErrTime=0;
    SDA_IN();
    IIC_SDA=1;
    Delay_us(1);
    IIC_SCL=1;
    Delay_us(1);
    while(READ_SDA){
        ucErrTime++;
        if(ucErrTime>250){
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL=0;
    return 0;
}

void IIC_Ack(void){
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=0;
    Delay_us(2);
    IIC_SCL=1;
    Delay_us(2);
    IIC_SCL=0;
}

void IIC_NAck(void){
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=1;
    Delay_us(2);
    IIC_SCL=1;
    Delay_us(2);
    IIC_SCL=0;
}

void IIC_Send_Byte(uint8_t txd){
    uint8_t t;
    SDA_OUT();
    IIC_SCL=0;
    for(t=0;t<8;t++){
        if((txd&0x80)>>7)
            IIC_SDA=1;
        else
            IIC_SDA=0;
        txd<<=1;
        Delay_us(2);
        IIC_SCL=1;
        Delay_us(2);
        IIC_SCL=0;
        Delay_us(2);
    }
}

uint8_t IIC_Read_Byte(uint8_t ack){
    uint8_t i,receive=0;
    SDA_IN();
    for(i=0;i<8;i++){
        IIC_SCL=0;
        Delay_us(2);
        IIC_SCL=1;
        receive<<=1;
        if(READ_SDA) receive++;
        Delay_us(1);
    }
    if(!ack) IIC_NAck();
    else IIC_Ack();
    return receive;
}

uint8_t IIC_Read_Bytes(uint8_t address,uint8_t reg,uint8_t *buf,uint8_t len){
    uint8_t i;
    IIC_Start();
    IIC_Send_Byte((address<<1)|0);
    if(IIC_Wait_Ack()){
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);
    if(IIC_Wait_Ack()){
        IIC_Stop();
        return 1;
    }
    IIC_Start();
    IIC_Send_Byte((address<<1)|1);
    if(IIC_Wait_Ack()){
        IIC_Stop();
        return 1;
    }
    for(i=0;i<len;i++){
        if(i<len-1) buf[i]=IIC_Read_Byte(1);
        else buf[i]=IIC_Read_Byte(0);
    }
    IIC_Stop();
    return 0;
}

uint8_t IIC_Send_Bytes(uint8_t address,uint8_t reg,uint8_t *buf,uint8_t len){
    uint8_t i;
    IIC_Start();
    IIC_Send_Byte((address<<1)|0);
    if(IIC_Wait_Ack()){
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);
    if(IIC_Wait_Ack()){
        IIC_Stop();
        return 1;
    }
    for(i=0;i<len;i++){
        IIC_Send_Byte(buf[i]);
        if(IIC_Wait_Ack()){
            IIC_Stop();
            return 1;
        }
    }
    IIC_Stop();
    return 0;
}

int32_t IICreadBytes(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length){
    uint32_t count = 0;
    IIC_Start();
    IIC_Send_Byte(dev);	
    if(IIC_Wait_Ack() == 1)return 0;
    IIC_Send_Byte(reg);
    if(IIC_Wait_Ack() == 1)return 0;
    IIC_Start();
    IIC_Send_Byte(dev+1); 
    if(IIC_Wait_Ack() == 1)return 0;
    for(count=0; count<length; count++){
        if(count!=length-1)data[count]=IIC_Read_Byte(1);
        else  data[count]=IIC_Read_Byte(0);	 
    }
    IIC_Stop();
    return 1;
}


int32_t IICwriteBytes(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length){
    uint32_t count = 0;
    IIC_Start();
    IIC_Send_Byte(dev);	   
    if(IIC_Wait_Ack() == 1)return 0;
    IIC_Send_Byte(reg);   
    if(IIC_Wait_Ack() == 1)return 0;
    for(count=0; count<length; count++){
        IIC_Send_Byte(data[count]);
        if(IIC_Wait_Ack() == 1)return 0;
    }
    IIC_Stop();
    return 1; 
}


