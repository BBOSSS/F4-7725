#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "bsp_exti.h"
#include "pwm.h" 
#include "timer.h" 
#include "bsp_sccb.h"
#include "bsp_ov7725.h"
#include "image_process.h" 
/********************************************************************/
extern uint8_t Ov7725_vsync;
extern void TIM3_Config(u16 arr,u16 psc);
/********************************************************************/
int main(void)
{ 
/*****************************��ʼ������***************************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);                               //��ʼ����ʱ����
	uart_init(115200);														 //��ʼ�����ڲ�����Ϊ115200
	LED_Init();                                    //LED
//	EXTI_Key_Config();                             //�����ⲿ�ж�
	TIM2_PWM_Init(20000-1,84-1,1500);  					   //��� 50Hz 
 	TIM4_PWM_Init(10000-1,42-1,3000);              //��� 200Hz
 	TIM3_Config(10000-1,8400-1);   							   //��ʱ����fps
  SCCB_Init();                                   //SCCB ��ʼ��
	Ov7725_GPIO_Config();                          //OV7725 IO ��ʼ��
	
	LED_ON;
	while(Ov7725_Init() != SUCCESS);               // ov7725 �Ĵ������ó�ʼ�� 
	LED_OFF;


	VSYNC_Init();	
	Ov7725_vsync = 0;                              // ov7725 ���ź��߳�ʼ�� 

	Motor_start();   //�������
	
/******************************�������***************************************/	                                      
	while(1)
	{
		if( Ov7725_vsync == 2 )											 //ͼ��д��FIFO��ɱ�־����ʼ��ȡͼ�񲢴���
		{		
			Get_Image_Data();	
	  	image_process();			
//			ImagDisp();					
			Ov7725_vsync = 0;			                     //ͼ������ɣ���ʼ��FIFOд������
		}
	}

}
