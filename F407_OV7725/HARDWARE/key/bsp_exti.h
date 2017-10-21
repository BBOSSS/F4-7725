#ifndef __EXTI_H
#define	__EXTI_H

#include "stm32f4xx.h"
#include "delay.h"
//Òý½Å¶¨Òå
/*******************************************************/
#define KEY1_INT_GPIO_PORT                GPIOA
#define KEY1_INT_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define KEY1_INT_GPIO_PIN                 GPIO_Pin_0
#define KEY1_INT_EXTI_PORTSOURCE          EXTI_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE           EXTI_PinSource0
#define KEY1_INT_EXTI_LINE                EXTI_Line0
#define KEY1_INT_EXTI_IRQ                 EXTI0_IRQn

#define KEY1_IRQHandler                   EXTI0_IRQHandler

/*******************************************************/


void EXTI_Key_Config(void);

#endif /* __EXTI_H */
