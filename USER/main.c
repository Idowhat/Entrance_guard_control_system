#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"     
#include "usmart.h" 
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"
#include "rtc.h"
#include "timer.h"
#include "Keyboard.h"
#include "unlocksystem.h"
#include "rc522_function.h"
#include "rc522_config.h"
#include "FingerPrint.h"

//时间修改
extern u8 flag_time_change_ok;
extern u8 timeset[20];




u8 del_number;//存放输出的卡片序号
//IC卡的数组
u8  IC_Password[20];    //={'1','2','3','4','5','6','\0'};
u8 	ucArray_ID[4];
u8  IC_User_Count;//用第41个地址放数量
u8  IC_Status;
u8  IC_Flag;
//测试用id
uint8_t passid[4]={0X50,0X47,0X85,0X29};
u8 text_IC_User_Count=1;

//flash size
u32 FLASH_SIZE=128*1024*1024;

 u8 EN_TimesShow=0;//用于开关时间的显示
//界面码设置
u8 Interface_Step[7];
u8 Step=0;
u8 Flag_SetInit=1;//保证一开始进主界面
u8 Interface_Code_Now=Main_Interface;
//密码的定义
u8  Password[20];    //={'1','2','3','4','5','6','\0'};
u8 	IN_Password[20];	
u8 Key_Value;
u8 Flag_End=0;
u8 Flag_Check_Password=0;
//按键按下标志
u8 KeyBoard_Status;
//毫秒计时器，用于输入密码时的闪烁
u16 ms_count;
//输入个数计数器
u8 PassWord_Count=0;
//密码相关的函数

void Check_Password(u8 *Flag_End)
{
	if (*Flag_End==1)
	{	u8 t;
		*Flag_End=0;
		
		for (t=0;Flag_Check_Password!=1;t++)
		{ if(Password[t]!=IN_Password[t]) {break;}  
			if((Password[t]=='\0')&&(IN_Password[t]=='\0')) 
			{Flag_Check_Password=1;}
			
		
		}
	
	
	}

}

void action (u8 *Flag_Check_Password,u8*Flag_End)
{	
	if (*Flag_Check_Password)
	{	extern u8 t;
		*Flag_Check_Password=0;
		LCD_Clear(BLACK);
		Show_Str(72,148,168,24,"已开锁",24,1);
		LED0=1;
		LED1=0;	
		delay_ms(1500);
		LED0=0;
		LED1=1;
		Interface_Forward(Interface_Step,&Step,&Interface_Code_Now,Management_Interface,&Flag_SetInit);
	
	}
	if(*Flag_End==2)
	{*Flag_End=0;
		W25QXX_Write(IN_Password,FLASH_SIZE-100,20);
		W25QXX_Read(Password,FLASH_SIZE-100,20);
		LCD_Clear(BLACK);
		Show_Str(72,148,168,24,"修改成功",24,1);
		delay_ms(1500);
		Step=0;
		Flag_SetInit=1;//进主界面
		Interface_Code_Now=Main_Interface;
		EN_TimesShow=1;
	}
	
	if(*Flag_End==3)
	{*Flag_End=0;
		LCD_Clear(BLACK);
		Show_Str(72,148,168,24,"已开锁",24,1);
		LED0=1;
		LED1=0;			
		delay_ms(1500);
		//delay_ms(1500);
		LED0=0;
		LED1=1;
		Step=0;
		Flag_SetInit=1;//进主界面
		Interface_Code_Now=Main_Interface;
		EN_TimesShow=1;
	}
}

//输入密码的界面
 int main(void)
 {	
	
	u8 t=0;	
	delay_init();	    	 //延时函数初始化
	Keyboard_Init();
	TIM3_Int_Init(99,719);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200				//初始化按键
	LCD_Init();			   		//初始化LCD   
	W25QXX_Init();				//初始化W25Q128
	font_init();
	LED_Init();
	W25QXX_Init();
	LCD_Clear(BLACK);
	usmart_dev.init(SystemCoreClock/1000000);
	RTC_Init();	
	W25QXX_Read(Password,FLASH_SIZE-100,20);//将密码读出
	W25QXX_Read(&IC_User_Count,FLASH_SIZE-60,1);
	W25QXX_Read(IC_Password,FLASH_SIZE-80,20);
	 
	LED_Init();
	RC522_Init ();
	PcdReset ();
	//指纹初始化
	Wake_Up_Init();
	Send_CMD_init();
	
	M500PcdConfigISOType ( 'A' );	
	LED0=0;
	LED1=1;
	while(1)
	{
	
	Interface_PassWord_Init(&Flag_SetInit,& EN_TimesShow,&ms_count,Interface_Code_Now,&PassWord_Count);
	Interface_PassWord_loop_Blink(&ms_count,PassWord_Count,Interface_Code_Now);
	Interface_PassWord_loop_Show(Key_Value,&PassWord_Count,KeyBoard_Status,Interface_Code_Now);
	Get_Password(Key_Value,IN_Password,&Flag_End,Interface_Code_Now,KeyBoard_Status);
	
	Interface_Change_Time_Init(&Flag_SetInit,&ms_count,Interface_Code_Now,&PassWord_Count);
	Interface_Change_Time_Blink(&ms_count,PassWord_Count,Interface_Code_Now);
	Interface_Change_Time_Show(Key_Value,&PassWord_Count,KeyBoard_Status,Interface_Code_Now);
	Get_Time_Change(Key_Value,timeset,&flag_time_change_ok,Interface_Code_Now,KeyBoard_Status);
	Time_Change_Action(Interface_Code_Now,&flag_time_change_ok);
	
	
	Interface_Main(& EN_TimesShow,&Flag_SetInit,Interface_Code_Now);
	Time_Auto_Show(&t,EN_TimesShow);	
	KeyBoard_Status=Keyboard_Scanf(&Key_Value);
	if((Interface_Code_Now==Main_Interface)&&(KeyBoard_Status==Flag_OK))
	{Interface_Forward(Interface_Step,&Step,&Interface_Code_Now,PassWord_Interface,&Flag_SetInit);}
	Check_Password(&Flag_End);
	action (&Flag_Check_Password,&Flag_End);
	Interface_Management_Init(&Flag_SetInit,Interface_Code_Now);
	Interface_Management_loop(KeyBoard_Status,Interface_Code_Now);
	IC_Status=Get_ucArray_ID(ucArray_ID ,Interface_Code_Now );
	Check_ucArray_ID(IC_Status,IC_User_Count,&Flag_End,ucArray_ID);
	
	Interface_IC_add_del_Init(&Flag_SetInit,Interface_Code_Now);
	Interface_IC_add_del_loop(KeyBoard_Status,Interface_Code_Now);
	Interface_IC_add_Init(&Flag_SetInit,Interface_Code_Now,IC_User_Count);
	Interface_IC_add_loop(Interface_Code_Now);
	Interface_IC_del_Init(&Flag_SetInit,Interface_Code_Now,IC_User_Count);
	Interface_IC_del_loop(KeyBoard_Status,Interface_Code_Now);
	Interface_IC_Verify_Init(&Flag_SetInit,Interface_Code_Now,IC_User_Count);
	Interface_IC_Verify_loop(Interface_Code_Now);
	
	Check_FINGER(Interface_Code_Now);
	Interface_Finger_add_del_Verify_Init(&Flag_SetInit,Interface_Code_Now);//无问题
	Interface_Finger_add_Init(&Flag_SetInit,Interface_Code_Now);//可能有问题
	Interface_Finger_del_Init(&Flag_SetInit,Interface_Code_Now);//问题概率较低
	Interface_Finger_del_loop(KeyBoard_Status,Interface_Code_Now);//问题概率较低
	Interface_Finger_Verify_Init(&Flag_SetInit,Interface_Code_Now);//问题:无法返回指纹编号原因：忘了未生成目标
	Interface_Finger_add_del_Verify_loop(KeyBoard_Status,Interface_Code_Now);//无问题
	
	ESC(Key_Value,KeyBoard_Status);//有问题，快速一直后退
	Home(Key_Value,KeyBoard_Status);
	} 
}
















