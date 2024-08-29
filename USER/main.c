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

//ʱ���޸�
extern u8 flag_time_change_ok;
extern u8 timeset[20];




u8 del_number;//�������Ŀ�Ƭ���
//IC��������
u8  IC_Password[20];    //={'1','2','3','4','5','6','\0'};
u8 	ucArray_ID[4];
u8  IC_User_Count;//�õ�41����ַ������
u8  IC_Status;
u8  IC_Flag;
//������id
uint8_t passid[4]={0X50,0X47,0X85,0X29};
u8 text_IC_User_Count=1;

//flash size
u32 FLASH_SIZE=128*1024*1024;

 u8 EN_TimesShow=0;//���ڿ���ʱ�����ʾ
//����������
u8 Interface_Step[7];
u8 Step=0;
u8 Flag_SetInit=1;//��֤һ��ʼ��������
u8 Interface_Code_Now=Main_Interface;
//����Ķ���
u8  Password[20];    //={'1','2','3','4','5','6','\0'};
u8 	IN_Password[20];	
u8 Key_Value;
u8 Flag_End=0;
u8 Flag_Check_Password=0;
//�������±�־
u8 KeyBoard_Status;
//�����ʱ����������������ʱ����˸
u16 ms_count;
//�������������
u8 PassWord_Count=0;
//������صĺ���

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
		Show_Str(72,148,168,24,"�ѿ���",24,1);
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
		Show_Str(72,148,168,24,"�޸ĳɹ�",24,1);
		delay_ms(1500);
		Step=0;
		Flag_SetInit=1;//��������
		Interface_Code_Now=Main_Interface;
		EN_TimesShow=1;
	}
	
	if(*Flag_End==3)
	{*Flag_End=0;
		LCD_Clear(BLACK);
		Show_Str(72,148,168,24,"�ѿ���",24,1);
		LED0=1;
		LED1=0;			
		delay_ms(1500);
		//delay_ms(1500);
		LED0=0;
		LED1=1;
		Step=0;
		Flag_SetInit=1;//��������
		Interface_Code_Now=Main_Interface;
		EN_TimesShow=1;
	}
}

//��������Ľ���
 int main(void)
 {	
	
	u8 t=0;	
	delay_init();	    	 //��ʱ������ʼ��
	Keyboard_Init();
	TIM3_Int_Init(99,719);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200				//��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
	W25QXX_Init();				//��ʼ��W25Q128
	font_init();
	LED_Init();
	W25QXX_Init();
	LCD_Clear(BLACK);
	usmart_dev.init(SystemCoreClock/1000000);
	RTC_Init();	
	W25QXX_Read(Password,FLASH_SIZE-100,20);//���������
	W25QXX_Read(&IC_User_Count,FLASH_SIZE-60,1);
	W25QXX_Read(IC_Password,FLASH_SIZE-80,20);
	 
	LED_Init();
	RC522_Init ();
	PcdReset ();
	//ָ�Ƴ�ʼ��
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
	Interface_Finger_add_del_Verify_Init(&Flag_SetInit,Interface_Code_Now);//������
	Interface_Finger_add_Init(&Flag_SetInit,Interface_Code_Now);//����������
	Interface_Finger_del_Init(&Flag_SetInit,Interface_Code_Now);//������ʽϵ�
	Interface_Finger_del_loop(KeyBoard_Status,Interface_Code_Now);//������ʽϵ�
	Interface_Finger_Verify_Init(&Flag_SetInit,Interface_Code_Now);//����:�޷�����ָ�Ʊ��ԭ������δ����Ŀ��
	Interface_Finger_add_del_Verify_loop(KeyBoard_Status,Interface_Code_Now);//������
	
	ESC(Key_Value,KeyBoard_Status);//�����⣬����һֱ����
	Home(Key_Value,KeyBoard_Status);
	} 
}
















