#ifndef __KEYBOARD_H
#define __KEYBOARD_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
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

void Keyboard_Init(void);//��ʼ��
u8 Keyboard_Scanf ( u8 *Key_Value);
		 				    
#endif
