#ifndef __IMAGE_PROCESS_H
#define __IMAGE_PROCESS_H
/********************************************************************/
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "bsp_ov7725.h"
/********************************************************************/
#define  Threshold   165
#define  White       254
#define  Black       0
#define  Mid_Line    82

/********************************************************************/
void image_process(void);

/********************************************************************/
#endif 
