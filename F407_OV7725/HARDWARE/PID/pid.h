#ifndef _PID_H
#define _PID_H

#include "stm32f4xx.h" 
#include "pwm.h"

#define  SERVO_PWM 		 TIM2->CCR1
#define  SERVO_CENTER  1500
#define  LEFT_MAX   	 1750
#define  RIGHT_MAX 		 1250
#define  MIN_ERR  	   1.5
#define  Kp        		 1.7
#define  Kd         	 5


void servo_control(void);
void motor_control(void);
#endif
