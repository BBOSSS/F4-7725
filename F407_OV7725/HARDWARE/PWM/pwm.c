#include "pwm.h"
#include "led.h"
#include "usart.h"
 
static void TIMx_GPIO_Config(void) 
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd (GENERAL_OCPWM_GPIO_CLK, ENABLE); 

	/* ��ʱ���������� */
	GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT,GENERAL_OCPWM_PINSOURCE,GENERAL_OCPWM_AF);  
	
	/* ͨ�ö�ʱ��PWM������� */															   
	GPIO_InitStructure.GPIO_Pin = GENERAL_OCPWM_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GENERAL_OCPWM_GPIO_PORT, &GPIO_InitStructure);
}
static void TIM4_GPIO_Config(void) 
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd (GENERAL_OCPWM_GPIO_CLK4, ENABLE); 

	/* ��ʱ���������� */
	GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT4,GENERAL_OCPWM_PINSOURCE4,GENERAL_OCPWM_AF4);  
	
	/* ͨ�ö�ʱ��PWM������� */															   
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
	
	// ����TIMx_CLK,x[2,3,4,5,12,13,14] 
  RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK, ENABLE);  

  /* �ۼ� TIM_Period�������һ�����»����ж�*/		
  //����ʱ����0������9999����Ϊ10000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Period = arr;       
	
	// ͨ�ö�ʱ��2ʱ��ԴTIMxCLK = HCLK/2=84MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = psc;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// ��ʼ����ʱ��TIMx, x[1,8]
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
	/* PWM���ģʽ���� */
	/* ����ΪPWMģʽ1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	/* PWM������ */
  TIM_OCInitStructure.TIM_Pulse = pluse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/* ʹ��ͨ��1 */
  TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);	
	/*ʹ��ͨ��1����*/
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	// ʹ�ܶ�ʱ��
	TIM_Cmd(GENERAL_TIM, ENABLE);	
}
static void TIM4_PWMOUTPUT_Config(u16 arr,u16 psc,u16 pluse)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// ����TIMx_CLK,x[2,3,4,5,12,13,14] 
  RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK4, ENABLE);  

  /* �ۼ� TIM_Period�������һ�����»����ж�*/		
  //����ʱ����0������9999����Ϊ10000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Period = arr;       
	
	// ͨ�ö�ʱ��2ʱ��ԴTIMxCLK = HCLK/2=84MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = psc;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// ��ʼ����ʱ��TIMx, x[1,8]
	TIM_TimeBaseInit(GENERAL_TIM4, &TIM_TimeBaseStructure);
	
	/* PWM���ģʽ���� */
	/* ����ΪPWMģʽ1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	/* PWM������ */
  TIM_OCInitStructure.TIM_Pulse = pluse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/* ʹ��ͨ��1 */
  TIM_OC1Init(GENERAL_TIM4, &TIM_OCInitStructure);	
	/*ʹ��ͨ��1����*/
	TIM_OC1PreloadConfig(GENERAL_TIM4, TIM_OCPreload_Enable);
	// ʹ�ܶ�ʱ��
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
