#include "timer.h"
#include "Keyboard.h"
extern unsigned char keysta[5][4];


//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
				unsigned   char i;
				static unsigned   char keyout =0;
				static unsigned   char keybuf[5][4]={
				{0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff}
				};
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
				TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
				
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












