#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"	
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "led.h"

#define GENERAL_OCPWM_PIN             GPIO_Pin_5              
#define GENERAL_OCPWM_GPIO_PORT       GPIOA                      
#define GENERAL_OCPWM_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define GENERAL_OCPWM_PINSOURCE				GPIO_PinSource5
#define GENERAL_OCPWM_AF							GPIO_AF_TIM2

#define GENERAL_OCPWM_PIN4             GPIO_Pin_6              
#define GENERAL_OCPWM_GPIO_PORT4       GPIOB                      
#define GENERAL_OCPWM_GPIO_CLK4        RCC_AHB1Periph_GPIOB
#define GENERAL_OCPWM_PINSOURCE4			 GPIO_PinSource6
#define GENERAL_OCPWM_AF4							 GPIO_AF_TIM4

/* 通用定时器 */
#define GENERAL_TIM           		    TIM2
#define GENERAL_TIM_CLK       		    RCC_APB1Periph_TIM2

#define GENERAL_TIM4           		    TIM4
#define GENERAL_TIM_CLK4       		    RCC_APB1Periph_TIM4

#define MOTOR_PWM  TIM4->CCR1

void TIM2_PWM_Init(u16 arr,u16 psc,u16 pluse);
void TIM4_PWM_Init(u16 arr,u16 psc,u16 pluse);

void Motor_start(void);

#endif
