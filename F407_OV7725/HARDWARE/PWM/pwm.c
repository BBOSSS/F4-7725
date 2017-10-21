#include "pwm.h"
#include "led.h"
#include "usart.h"
 
static void TIMx_GPIO_Config(void) 
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd (GENERAL_OCPWM_GPIO_CLK, ENABLE); 

	/* 定时器复用引脚 */
	GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT,GENERAL_OCPWM_PINSOURCE,GENERAL_OCPWM_AF);  
	
	/* 通用定时器PWM输出引脚 */															   
	GPIO_InitStructure.GPIO_Pin = GENERAL_OCPWM_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GENERAL_OCPWM_GPIO_PORT, &GPIO_InitStructure);
}
static void TIM4_GPIO_Config(void) 
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd (GENERAL_OCPWM_GPIO_CLK4, ENABLE); 

	/* 定时器复用引脚 */
	GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT4,GENERAL_OCPWM_PINSOURCE4,GENERAL_OCPWM_AF4);  
	
	/* 通用定时器PWM输出引脚 */															   
	GPIO_InitStructure.GPIO_Pin = GENERAL_OCPWM_PIN4;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GENERAL_OCPWM_GPIO_PORT4, &GPIO_InitStructure);
}

static void TIM_PWMOUTPUT_Config(u16 arr,u16 psc,u16 pluse)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// 开启TIMx_CLK,x[2,3,4,5,12,13,14] 
  RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK, ENABLE);  

  /* 累计 TIM_Period个后产生一个更新或者中断*/		
  //当定时器从0计数到9999，即为10000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Period = arr;       
	
	// 通用定时器2时钟源TIMxCLK = HCLK/2=84MHz 
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = psc;	
  // 采样时钟分频
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // 计数方式
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// 初始化定时器TIMx, x[1,8]
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
	/* PWM输出模式配置 */
	/* 配置为PWM模式1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	/* PWM脉冲宽度 */
  TIM_OCInitStructure.TIM_Pulse = pluse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/* 使能通道1 */
  TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);	
	/*使能通道1重载*/
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	// 使能定时器
	TIM_Cmd(GENERAL_TIM, ENABLE);	
}
static void TIM4_PWMOUTPUT_Config(u16 arr,u16 psc,u16 pluse)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// 开启TIMx_CLK,x[2,3,4,5,12,13,14] 
  RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK4, ENABLE);  

  /* 累计 TIM_Period个后产生一个更新或者中断*/		
  //当定时器从0计数到9999，即为10000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Period = arr;       
	
	// 通用定时器2时钟源TIMxCLK = HCLK/2=84MHz 
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = psc;	
  // 采样时钟分频
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // 计数方式
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// 初始化定时器TIMx, x[1,8]
	TIM_TimeBaseInit(GENERAL_TIM4, &TIM_TimeBaseStructure);
	
	/* PWM输出模式配置 */
	/* 配置为PWM模式1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	/* PWM脉冲宽度 */
  TIM_OCInitStructure.TIM_Pulse = pluse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/* 使能通道1 */
  TIM_OC1Init(GENERAL_TIM4, &TIM_OCInitStructure);	
	/*使能通道1重载*/
	TIM_OC1PreloadConfig(GENERAL_TIM4, TIM_OCPreload_Enable);
	// 使能定时器
	TIM_Cmd(GENERAL_TIM4, ENABLE);	
}

void TIM2_PWM_Init(u16 arr,u16 psc,u16 pluse)
{
	TIMx_GPIO_Config();
	
  TIM_PWMOUTPUT_Config(arr,psc,pluse);
}
void TIM4_PWM_Init(u16 arr,u16 psc,u16 pluse)
{
	TIM4_GPIO_Config();
	
  TIM4_PWMOUTPUT_Config(arr,psc,pluse);
}

void Motor_start(void)
{
	delay_ms(100); 
	MOTOR_PWM+=100;
	
	delay_ms(100);
	MOTOR_PWM+=100;
	
	delay_ms(100);
	MOTOR_PWM+=150;
	
	delay_ms(100);
	MOTOR_PWM+=150;
	
	delay_ms(100);
	MOTOR_PWM+=150;
	
	delay_ms(100);
	MOTOR_PWM+=150;
	
	delay_ms(100);
	MOTOR_PWM+=150;
}
