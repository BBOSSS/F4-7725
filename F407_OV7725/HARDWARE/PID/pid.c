#include "pid.h" 

#include "bsp_ov7725.h"
#include "image_process.h"

extern float current_err;
extern float pre_err;
extern u8 front_flag;
extern u8 final_flag;
__IO u8 stop_flag = 0;
void servo_control(void)
{
	float temp;

	if( (current_err<MIN_ERR) && (current_err>-MIN_ERR) ) //ƫ��̫С �������� 
	{
		return;
	}
	temp = Kp*current_err + Kd*(current_err-pre_err);
	
	pre_err = current_err;
	
	temp = SERVO_CENTER - temp + 15;
	
	if( temp > LEFT_MAX ) temp = LEFT_MAX;
	
	if( temp < RIGHT_MAX ) temp = RIGHT_MAX;
	if(front_flag==1)
	{
		temp=1650;
		front_flag=2;
	}
	SERVO_PWM=temp;
}

void motor_control(void)
{
	if(final_flag > 2)
	{
		MOTOR_PWM = 2800;
//		MOTOR_PWM = 3000;
	}	
	else if((current_err<-10))
	{
		MOTOR_PWM = 2900;
	}
	else 
		MOTOR_PWM = 3800;
	
	//final_flag=0;
}



