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
/*****************************初始化配置***************************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);                               //初始化延时函数
	uart_init(115200);														 //初始化串口波特率为115200
	LED_Init();                                    //LED
//	EXTI_Key_Config();                             //按键外部中断
	TIM2_PWM_Init(20000-1,84-1,1500);  					   //舵机 50Hz 
 	TIM4_PWM_Init(10000-1,42-1,3000);              //电机 200Hz
 	TIM3_Config(10000-1,8400-1);   							   //定时计算fps
  SCCB_Init();                                   //SCCB 初始化
	Ov7725_GPIO_Config();                          //OV7725 IO 初始化
	
	LED_ON;
	while(Ov7725_Init() != SUCCESS);               // ov7725 寄存器配置初始化 
	LED_OFF;


	VSYNC_Init();	
	Ov7725_vsync = 0;                              // ov7725 场信号线初始化 

	Motor_start();   //启动电机
	
/******************************配置完成***************************************/	                                      
	while(1)
	{
		if( Ov7725_vsync == 2 )											 //图像写入FIFO完成标志，开始获取图像并处理
		{		
			Get_Image_Data();	
	  	image_process();			
//			ImagDisp();					
			Ov7725_vsync = 0;			                     //图像处理完成，开始往FIFO写入数据
		}
	}

}
