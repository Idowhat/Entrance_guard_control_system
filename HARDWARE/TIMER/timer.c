#include "timer.h"
#include "Keyboard.h"
extern unsigned char keysta[5][4];


//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
				unsigned   char i;
				static unsigned   char keyout =0;
				static unsigned   char keybuf[5][4]={
				{0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff}
				};
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
				TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
				
				keybuf[0][keyout]=(keybuf[0][keyout]<<1)|KeyIn0;
				keybuf[1][keyout]=(keybuf[1][keyout]<<1)|KeyIn1;
				keybuf[2][keyout]=(keybuf[2][keyout]<<1)|KeyIn2;
				keybuf[3][keyout]=(keybuf[3][keyout]<<1)|KeyIn3;
				keybuf[4][keyout]=(keybuf[4][keyout]<<1)|KeyIn4;
				
				for(i=0;i<5;i++)
					{
						if((keybuf[i][keyout]&0x0f)==0x00)
							keysta[i][keyout]=0;
					 else if ((keybuf[i][keyout]&0x0f)==0x0f)
						 keysta[i][keyout]=1;
						
					}
					keyout++;
					keyout=keyout&0x03;
					switch (keyout)
						{
							case 0:KeyOut3=1; KeyOut0=0; break;
							case 1:KeyOut0=1; KeyOut1=0; break;
							case 2:KeyOut1=1; KeyOut2=0; break;
							case 3:KeyOut2=1; KeyOut3=0; break;
						default : break;
						}
		}
}












