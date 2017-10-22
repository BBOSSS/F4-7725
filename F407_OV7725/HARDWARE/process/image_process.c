#include "image_process.h"
#include "pid.h"
/**********************************************************/
__IO u8 mid_line[120]={0};
__IO 	float current_err = 0;
__IO 	float pre_err = 0;

//u8 lost_count=0;
__IO u8 front_flag=0;
__IO u8 final_flag_white=0;
__IO u8 final_flag_black=0;
__IO u8 final_white_count=0;
__IO u8 final_black_count=0;
extern uint8_t image_data[120][160];
/**********************************************************/
/*************************滤波***************************/
//static void Filter(void)
//{
//	u16 i,j,k;
//	for( i=1; i<119; i++)
//	{
//		for( j=1; j<159; j++)
//		{
//			if(image_data[i][j]==White) //white
//			{
//				k = 0;//计算白点周围黑点的个数
//				if(image_data[i-1][j-1]==Black) k++;
//				if(image_data[i-1][j]==Black) k++;
//				if(image_data[i-1][j+1]==Black) k++;
//				if(image_data[i][j-1]==Black) k++;
//				if(image_data[i][j+1]==Black) k++;
//				if(image_data[i+1][j-1]==Black) k++;
//				if(image_data[i+1][j]==Black) k++;
//				if(image_data[i+1][j+1]==Black) k++;
//				//大于等于4个即认为是噪点
//				if( k > 4 ) image_data[i][j] = Black;
//					else  image_data[i][j] = White;
//			}
//			if(image_data[i][j]==Black) //Black
//			{
//				k = 0;
//				if(image_data[i-1][j-1]==White) k++;
//				if(image_data[i-1][j]==White) k++;
//				if(image_data[i-1][j+1]==White) k++;
//				if(image_data[i][j-1]==White) k++;
//				if(image_data[i][j+1]==White) k++;
//				if(image_data[i+1][j-1]==White) k++;
//				if(image_data[i+1][j]==White) k++;
//				if(image_data[i+1][j+1]==White) k++;
//				
//				if( k > 4 ) image_data[i][j] = White;
//					else  image_data[i][j] = Black;
//			}
//		}
//	}
//}
/************************提取中线*********************************/	
static void get_mid_line(void)
{
	u16 i, j;
	u8 left_line,right_line;
	u8 left_line_pre,right_line_pre;

  for( i=119; i>0; i--)
	{
		for( j=0; j<158; j++)//寻找左边界线
		{
			if((image_data[i][j]==White)&&(image_data[i][j+1]==White)&&(image_data[i][j+2]==White))
			{
				left_line = j;
				left_line_pre = left_line;
				break;
			}
				else //找不到边界线
				{
					left_line = left_line_pre;
				}
		}
		for( j=159; j>2; j--)//寻找右边界线
		{
			if((image_data[i][j]==White)&&(image_data[i][j-1]==White)&&(image_data[i][j-2]==White))
			{
				right_line = j;
				right_line_pre = right_line;
				break;
			}
				else //找不到边界线
				{
					right_line = right_line_pre;
				}
		}

		if((i > 70) && (i < 81))//60-90行判断终点线
		{
			for( j=10; j<150; j++)
			{
				if(image_data[i][j] == White)
					final_white_count++;
				else if(image_data[i][j] == Black)
					final_black_count++;
			}
							
			if(final_white_count > 100)
			{
				final_flag_white++;
			}
			else if(final_black_count > 80)
			{
				final_flag_black++;
			}
			final_white_count = 0;
			final_black_count = 0;
		}
		
		mid_line[i] = (left_line+right_line)/2; //计算中线
	}
}

/***************************计算中线偏差值**************************/
static float get_error(void)
{
	u8 i;
	
	float temp,tempf;
	float Error_sum=0;
	float	Error_sumf=0;
	float error;
	for(i=5;i<30;i++)
	{
		tempf = mid_line[i] - Mid_Line;
		Error_sumf += tempf;
	}
	Error_sumf=Error_sumf/25;
	if(Error_sumf < -30)
		front_flag = 1;
	Error_sumf = 0;
	for( i=30; i<70; i++)  //40行做基准
	{
		temp = mid_line[i] - Mid_Line;
		Error_sum += temp;
	}
	error = Error_sum/40;
	Error_sum = 0;
	
	return error;
}
/**********************上位机显示中线*******************************/
static void disp_mid_line(void)
{
	u16 i,j;

	for( i=0; i<120; i++)
	{
		j = mid_line[i];
		image_data[i][j-1] = 0; //三个像素点加粗显示
		image_data[i][j] = 0;   //中线填充黑色
		image_data[i][j+1] = 0;
	}
	
	Usart_Senddata( USART1,0xff );
	
	for( i = 0; i < 120; i++) //上位机显示提取黑线结果
	{
		for( j = 0; j < 160; j++)
		{
				if(image_data[i][j] == 255 ) image_data[i][j] = 254;
				Usart_Senddata( USART1,image_data[i][j] );	
		}
	}
}


/***********************图像处理**********************************/
void image_process(void) 
{	
//	Filter();                  //滤除噪点
	
	get_mid_line();            //提取中线
	
//	disp_mid_line();           //显示中线

  current_err = get_error(); //获取偏差值
	
 	motor_control();           //电机控制
	
  servo_control();           //舵机控制
}
/*****************************************************************/
