#include "control.h"

PID_TypeDef position_pid;
PID_TypeDef angle_pid;
int8_t auto_velocity=0;

uint8_t angle_pid_enable=0;
uint8_t position_pid_enable=0;
uint8_t position_master_enable=0;
uint8_t angle_master_enable=0;

/* pid basic function*/
void pid_init(void){
    position_pid.SetPoint=80;
    position_pid.ActualValue=0.0;
    position_pid.SumError=0.0;
    position_pid.Error=0.0;
    position_pid.LastError=0.0;
    position_pid.PrevError=0.0;
    position_pid.Proportion=KP_POSITION;
    position_pid.Integral=KI_POSITION;
    position_pid.Derivative=KD_POSITION;
    angle_pid.SetPoint=0;
    angle_pid.ActualValue=0.0;
    angle_pid.SumError=0.0;
    angle_pid.Error=0.0;
    angle_pid.LastError=0.0;
    angle_pid.PrevError=0.0;
    angle_pid.Proportion=KP_ANGLE;
    angle_pid.Integral=KI_ANGLE;
    angle_pid.Derivative=KD_ANGLE;
}

void set_pid_target(PID_TypeDef *pid,float target){
    pid->SetPoint=target;
}

void set_pid_parameter(PID_TypeDef *pid,float kp,float ki,float kd){
    pid->Proportion=kp;
    pid->Integral=ki;
    pid->Derivative=kd;
}

/*pid control angle function*/
float angle_pid_update(PID_TypeDef *PID,float feedback_value){
    /*compute error*/
    PID->Error=(float)(PID->SetPoint-feedback_value);
    /*compute deadline*/
    if((PID->Error>=-ANGLE_DEADLINE)&&(PID->Error<=ANGLE_DEADLINE)) PID->Error=0;
    /*intergral bound*/ 
    if(PID->Error>ANGLE_INTERGRAL_BOUND) PID->Error=ANGLE_INTERGRAL_BOUND;
    if(PID->Error<-ANGLE_INTERGRAL_BOUND) PID->Error=-ANGLE_INTERGRAL_BOUND;                                           
    /*compute output*/
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          
                        + (PID->Integral * PID->Error)                                             
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError)); 
    if(PID->ActualValue>SPEED_BOUND) PID->ActualValue=SPEED_BOUND;
    if(PID->ActualValue<-SPEED_BOUND) PID->ActualValue=-SPEED_BOUND;
    /*update error*/
    PID->PrevError = PID->LastError;                                       
    PID->LastError = PID->Error;
    return PID->ActualValue;
}

void angle_pid_control(void){
    if(angle_pid_enable==1){
        static uint32_t outer_ring_time=0;
        float feedback_value=IMU_Structure.angle[2];
        float speed_control_value=0;
        /*outer ring*/
        if(outer_ring_time++%2==0){
            speed_control_value=angle_pid_update(&angle_pid,feedback_value);
            auto_velocity=(int8_t)(speed_control_value);
        }
        /*inner ring*/
        standard_clockwise(auto_velocity);
    }
}

/*pid control position function*/
float position_pid_update(PID_TypeDef *PID,float feedback_value){
    /*compute error*/
    PID->Error=(float)(feedback_value-PID->SetPoint);
    /*compute deadline*/
    if((PID->Error>=-POSITION_DEADLINE)&&(PID->Error<=POSITION_DEADLINE)){
        position_pid_enable=0;
        standard_stop();
    } 
    /*intergral bound*/ 
    if(PID->Error>POSITION_INTERGRAL_BOUND) PID->Error=POSITION_INTERGRAL_BOUND;
    if(PID->Error<-POSITION_INTERGRAL_BOUND) PID->Error=-POSITION_INTERGRAL_BOUND;                                           
    /*compute output*/
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          
                        + (PID->Integral * PID->Error)                                             
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError)); 
    if(PID->ActualValue>SPEED_BOUND) PID->ActualValue=SPEED_BOUND;
    if(PID->ActualValue<-SPEED_BOUND) PID->ActualValue=-SPEED_BOUND;
    /*update error*/
    PID->PrevError = PID->LastError;                                       
    PID->LastError = PID->Error;
    return PID->ActualValue;
}

void position_pid_control(void){
    if(position_pid_enable==1){
        static uint32_t outer_ring_time=0;
        float feedback_value=(float)(openmv_structure.target_x);
        float speed_control_value=0;
        /*outer ring*/
        if(outer_ring_time++%2==0){
            speed_control_value=position_pid_update(&position_pid,feedback_value);
            auto_velocity=(int8_t)(speed_control_value);
        }
        /*inner ring*/
        standard_right(auto_velocity);
    }
}

void master_position_control(float feedback_value){
    if(position_master_enable==1){
        float position_error=feedback_value-80.0;
        if(position_error>=-POSITION_DEADLINE&&position_error<=POSITION_DEADLINE){
            position_master_enable=0;
            standard_stop();
        } 
        else if(POSITION_DEADLINE<position_error&&position_error<=10) standard_right(5);
        else if(-10<=position_error&&position_error<-POSITION_DEADLINE) standard_left(5);
        else if(position_error>10) standard_right(15);
        else if(position_error<10) standard_left(15);
    }
}

void master_angle_control(float target,float feedback_value){

}




