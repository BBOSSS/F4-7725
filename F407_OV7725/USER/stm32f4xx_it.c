/* Includes --------------------------------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "led.h"
#include "bsp_exti.h"
#include "bsp_ov7725.h"
#include "pwm.h"
#include "pid.h"
/*------------------------------------------------------------------------------------------------------*/
extern u8 Ov7725_vsync;
//__IO u32 fps = 0;
u8 time1 = 0;
extern u8 stop_flag;
/*------------------------------------------------------------------------------------------------------*/
/* ov7725 ���ж� ������� */
void macOV7725_VSYNC_EXTI_INT_FUNCTION ( void )
{
    if ( EXTI_GetITStatus(macOV7725_VSYNC_EXTI_LINE) != RESET ) 	//���EXTI_Line0��·�ϵ��ж������Ƿ��͵���NVIC 
    {		
        if( Ov7725_vsync == 0 )
        {
            FIFO_WRST_L(); 	                      //����ʹFIFOд(����from����ͷ)ָ�븴λ
            FIFO_WE_H();	                        //����ʹFIFOд����
            
            Ov7725_vsync = 1;	   	
            FIFO_WE_H();                          //ʹFIFOд����
            FIFO_WRST_H();                        //����ʹFIFOд(����from����ͷ)ָ���˶�
        }
        else if( Ov7725_vsync == 1 )
        {
					//fps++;
            FIFO_WE_L();                          //����ʹFIFOд��ͣ
            Ov7725_vsync = 2;						
        }        
        EXTI_ClearITPendingBit(macOV7725_VSYNC_EXTI_LINE);		    //���EXTI_Line0��·�����־λ        
    }    
}
/*------------------------------------------------------------------------------------------------------*/

void TIM3_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		time1++;
		if( time1 == 8 ) //30s��ʱֹͣ���
		{
//			time1 = 0;
			stop_flag = 1;
			MOTOR_PWM = 3000;
		}
		LED_TOGGLE;//DS1��ת
//		printf("\n\r FPS = %d \r\n",fps);
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
/*------------------------------------------------------------------------------------------------------*/

void KEY1_IRQHandler(void)
{
	delay_ms(10);
	if(EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) 
	{	
		LED_TOGGLE;
		SERVO_PWM+=200;
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);     
	}  
}
/********************************************************************************************************/


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
 
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
