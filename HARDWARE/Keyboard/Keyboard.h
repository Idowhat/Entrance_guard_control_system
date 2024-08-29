#ifndef __KEYBOARD_H
#define __KEYBOARD_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define Flag_OK 0x01
#define Flag_ERROR 0x00
#define KeyOut0 PCout(0)//d0
#define KeyOut1 PCout(1)//d1
#define KeyOut2 PCout(2)//d2
#define KeyOut3 PCout(3)//d3

#define KeyIn0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//
#define KeyIn1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define KeyIn2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define KeyIn3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)
#define KeyIn4  GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15)//oe

void Keyboard_Init(void);//初始化
u8 Keyboard_Scanf ( u8 *Key_Value);
		 				    
#endif
