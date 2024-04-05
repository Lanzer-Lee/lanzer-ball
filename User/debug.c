#include "debug.h"

float debug_Kp=0,debug_Ki=0,debug_Kd=0;

void debug_command_process(void){
    //uint8_t i=0;
	if(Serial_RxFlag_USART1==1){
		if(Serial_RxPacket_USART1[0]=='$'){
			control_enable();
			if(strcmp(Serial_RxPacket_USART1,"$IMU!")==0){
				IMU_Data_Process();	
				printf("IMU=%f\r\n",IMU_Structure.angle[2]);
			}
            else if(Serial_RxPacket_USART1[1]=='('){
				sscanf(Serial_RxPacket_USART1,"$(%f,%f,%f)!",&debug_Kp,&debug_Ki,&debug_Kd);
				printf("Kp=%.2f,Ki=%.2f,Kd=%.2f\r\n",debug_Kp,debug_Ki,debug_Kd);
				set_pid_parameter(&position_pid,debug_Kp,debug_Ki,debug_Kd);
            }
			Serial_SendString(USART1,Serial_RxPacket_USART1);
		}
		if(Serial_RxPacket_USART1[0]=='@'||Serial_RxPacket_USART1[0]=='#'){
			Serial_SendString(USART1,Serial_RxPacket_USART1);
			Serial_SendString(USART3,Serial_RxPacket_USART1);
		}
		Serial_RxFlag_USART1=0;
	}	
}

void control_enable(void){
	if(Serial_RxPacket_USART1[1]=='0'){
		TIM_Cmd(TIM3,DISABLE);
		position_pid_enable=0;
		angle_pid_enable=0;
		angle_expert_enable=0;
		position_expert_enable=0;
		pid_init();
		return;
	}
	else if(strcmp(Serial_RxPacket_USART1,"$position_pid!")==0){
		position_pid_enable=1;
	} 
	/*
	else if(strcmp(Serial_RxPacket_USART1,"position_master")==0){
		position_master_enable=1;
		control_call_back=master_position_control;
	} 
	*/
	else if(strcmp(Serial_RxPacket_USART1,"$angle_pid!")==0){
		angle_pid_enable=1;
	} 
	/*
	else if(strcmp(Serial_RxPacket_USART1,"angle_master")==0){
		angle_master_enable=1;
		control_call_back=master_angle_control;
	} 
	*/
	TIM_Cmd(TIM3,ENABLE);
}
