#include "unlocksystem.h"
#include "lcd.h"
#include "sys.h"
#include "stdlib.h"
#include "text.h"
#include "delay.h"
#include "rtc.h"
#include "Keyboard.h"
#include "rc522_config.h"
#include "rc522_function.h"
#include "w25qxx.h"
#include "FingerPrint.h"
u8 Get_Password_Count=0;
u8 Finger_CodeNum;
u8 Finger_Status;
u8 ucArray_CodeNum;

u16 syear;
	u8 smon,sday,hour,min,sec;


u8 flag_time_change_ok=0;
u8 timeset[20];


extern u8 Time_Out_Count;
extern u8 Interface_Step[7];
extern u8 Step;
extern u8 Flag_SetInit;
extern u8 Interface_Code_Now;
extern u8 Key_Value;
extern u8 KeyBoard_Status;
extern u8  IC_Status;
extern u8  IC_User_Count;
extern u8  IC_Password[20];
extern u8 	ucArray_ID[4];
extern u32 FLASH_SIZE;
extern u8 del_number;
extern u8 EN_TimesShow;
extern u8 Flag_End;
extern u8 Finger_User_Count;
void Interface_Main(u8 *TimeEnable,u8 *Init,u8 interface_code)
{
	if((*Init)&&(interface_code==Main_Interface))
	{*TimeEnable=1;
		*Init=0;
	LCD_Clear(BLACK);
	POINT_COLOR=RED;
	Show_Str(48,136,192,24,"欢迎使用智能",24,1);	
	Show_Str(48,160,192,24,"门禁控制系统",24,1); 
	Show_Str(56,229,184,16,"按任意键进入系统",16,1); 
	POINT_COLOR=WHITE;
	Show_Str(96,290,144,24,"作者：李志尧",24,1);
	POINT_COLOR=BLUE; 
	LCD_ShowString(72,44,168,24,24,"  :  :  ");	
	LCD_ShowString(6,68,168,24,24,"    -  -  ");}
}
void Interface_PassWord_Init(u8 *Init,u8 *TimeEnable,u16* MS_Count,u8 interface_code,u8 * count)
{
	if((*Init)&&((interface_code==PassWord_Interface)||(interface_code==PassWord_Interface_Change)))
	{* MS_Count=0;
		Get_Password_Count=0;
		*count=0;
 *Init=0;//进来时只执行一次
*TimeEnable=0;//关闭时间显示
	LCD_Clear(BLACK);
	Show_Str(72,124,168,24,"您输入的",24,1);
	Show_Str(78,148,162,24,"密码为",24,1);
	LCD_ShowString(150,148,90,24,24,":");}
}
void Interface_PassWord_loop_Blink(u16* MS_Count,u8 count,u8 interface_code)
{
	if((interface_code==PassWord_Interface)||(interface_code==PassWord_Interface_Change))
	{delay_ms(1);
	++(*MS_Count);
	if(*MS_Count==500)
		LCD_ShowString(count*12,172,240,24,24,"_");
	if(*MS_Count==1000)
	{*MS_Count=0;LCD_ShowString(count*12,172,240,24,24," "); }}
	
}
	
void Interface_PassWord_loop_Show(u8 Key_Value,u8 * count,u8 Keyboard_Status,u8 interface_code)
{
	if(((interface_code==PassWord_Interface)||(interface_code==PassWord_Interface_Change))&&(Keyboard_Status==Flag_OK))
	{
		if (Key_Value=='z')
		{LCD_ShowString((*count)*12,172,240,24,24," ");
		 --(*count);}
		if((Key_Value!='y')&&(Key_Value!='z'))
		{++(*count);
		LCD_ShowString((*count)*12-12,172,240,24,24,"*");
		}	
		if (Key_Value=='y')
		*count=0;	
	}

}


void ESC(u8 keyvalue,u8 Keyboard_Status)
{
if((keyvalue=='b')&&(Keyboard_Status==Flag_OK))
{
	delay_ms(16);
	Keyboard_Status=Keyboard_Scanf(&Key_Value);
Interface_Back(Interface_Step,&Step,&Interface_Code_Now,&EN_TimesShow,&Flag_SetInit);
}


}
void Interface_Back(u8*array,u8*step,u8*Interface_Code_Now_p,u8 *enable,u8 *Init)
{
--(*step);	
*Interface_Code_Now_p=*(array+(*step));
	*Init=1;
	if((*Interface_Code_Now_p)==Main_Interface)
	{*enable=1;}
	delay_ms(16);KeyBoard_Status=Keyboard_Scanf(&Key_Value);
}
void Interface_Forward(u8*array,u8*step,u8*Interface_Code_Now_p,u8 interface_code,u8*Init_p)
{
*(array+(*step))=*Interface_Code_Now_p;
	++(*step);
	*Interface_Code_Now_p=interface_code;
	*Init_p=1;
	delay_ms(16);KeyBoard_Status=Keyboard_Scanf(&Key_Value);
	
}
void Get_Password(u8 Key_value ,u8 *IN_Password_P,u8* Flag_End_P,u8 interface_code,u8 Keyboard_Status)
{			
			
			if ((Keyboard_Status == Flag_OK )&&(interface_code==PassWord_Interface))
				{	
					
					if( Key_value=='y')
					{*Flag_End_P=1;*(IN_Password_P+Get_Password_Count)='\0';Get_Password_Count=0;}
					else if(Key_value=='z')
					{Get_Password_Count--;}
					else
					{*(IN_Password_P+Get_Password_Count)=Key_value; Get_Password_Count++;}				
				}
				if ((Keyboard_Status == Flag_OK )&&(interface_code==PassWord_Interface_Change))
				{	
					
					if( Key_value=='y')
					{*Flag_End_P=2;*(IN_Password_P+Get_Password_Count)='\0';Get_Password_Count=0;}
					else if(Key_value=='z')
					{Get_Password_Count--;}
					else
					{*(IN_Password_P+Get_Password_Count)=Key_value; Get_Password_Count++;}				
				}

				
				
}
void Time_Auto_Show(u8* t_P,u8 enable)
{
	if((enable)&&((*t_P)!=calendar.sec))
				{
					*t_P=calendar.sec;
					LCD_ShowNum(6,68,calendar.w_year,4,24);									  
					LCD_ShowNum(66,68,calendar.w_month,2,24);									  
					LCD_ShowNum(102,68,calendar.w_date,2,24);	 
					switch(calendar.week)
					{
						case 0:
							LCD_ShowString(126,68,114,24,24,"   Sunday");
							break;
						case 1:
							LCD_ShowString(126,68,114,24,24,"   Monday");
							break;
						case 2:
							LCD_ShowString(126,68,114,24,24,"  Tuesday");
							break;
						case 3:
							LCD_ShowString(126,68,114,24,24,"Wednesday");
							break;
						case 4:
							LCD_ShowString(126,68,114,24,24," Thursday");
							break;
						case 5:
							LCD_ShowString(126,68,114,24,24,"   Friday");
							break;
						case 6:
							LCD_ShowString(126,68,114,24,24," Saturday");
							break;  
					}
					LCD_ShowNum(72,44,calendar.hour,2,24);									  
					LCD_ShowNum(108,44,calendar.min,2,24);									  
					LCD_ShowNum(144,44,calendar.sec,2,24);
				}

}
void Interface_Management_Init(u8 *Init,u8 interface_code)
{
if((*Init)&&(interface_code==Management_Interface))
{
*Init=0;
LCD_Clear(BLACK);
LCD_ShowString(54,112,186,24,24,"F1:");
Show_Str(90,112,186,24,"修改密码",24,1);
LCD_ShowString(54,136,186,24,24,"F2:");
Show_Str(90,136,186,24,"指纹管理",24,1);
LCD_ShowString(54,160,186,24,24,"#:IC");
Show_Str(102,160,186,24,"卡管理",24,1);
LCD_ShowString(54,184,186,24,24,"* :");
Show_Str(90,184,186,24,"修改时间",24,1);	

}

}	
/*Interface_Forward(Interface_Step,&Step,&Interface_Code_Now,PassWord_Interface,&Flag_SetInit);*/
void Interface_Management_loop(u8 Keyboard_Status,u8 interface_code)//未完待续
{
if((interface_code==Management_Interface)&&(Keyboard_Status==Flag_OK))
{
if (Key_Value=='A')
{Interface_Forward(Interface_Step , &Step,&Interface_Code_Now,PassWord_Interface_Change,&Flag_SetInit);}

if (Key_Value=='B')
{Interface_Forward(Interface_Step , &Step,&Interface_Code_Now,Finger_add_del_Verify_Interface,&Flag_SetInit);}

if (Key_Value=='#')
{Interface_Forward(Interface_Step , &Step,&Interface_Code_Now,IC_add_del_Interface,&Flag_SetInit);}

if (Key_Value=='*')
{Interface_Forward(Interface_Step , &Step,&Interface_Code_Now,Time_Change_Interface,&Flag_SetInit);}

}


}

void Check_ucArray_ID(u8 IC_Status,u8 IC_User_Count,u8*Flag_End,u8*ucArray_ID)
{ u8 ii;
	u8 iii;
 if(IC_Status==MI_OK)
 {
 for(ii=0;ii<IC_User_Count;ii++)
	 {
	 for(iii=0;iii<4;iii++)
		 {
			 if((*(ucArray_ID+iii))!=IC_Password[ii*4+iii])break;
			 if(iii==3) *Flag_End=3;
		 }
		 
	 
	 }
 
 }

}
void Interface_IC_add_del_Init(u8 *Init,u8 interface_code)
{
if((*Init)&&(interface_code==IC_add_del_Interface))
{
*Init=0;
LCD_Clear(BLACK);
LCD_ShowString(54,112,186,24,24,"F1:");
Show_Str(90,112,186,24,"添加卡片",24,1);
LCD_ShowString(54,136,186,24,24,"F2:");
Show_Str(90,136,186,24,"删除卡片",24,1);	
LCD_ShowString(54,160,186,24,24," #:");
Show_Str(90,160,186,24,"识别卡片",24,1);		

}



}

/////////添加


void Interface_Change_Time_Init(u8 *Init,u16* MS_Count,u8 interface_code,u8 * count)
{
	if((*Init)&&(interface_code==Time_Change_Interface))
	{* MS_Count=0;
		*count=0;
 *Init=0;//进来时只执行一次
LCD_Clear(BLACK);
Show_Str(60,100,180,24,"请依次输入",24,1);
Show_Str(48,124,192,24,"年月日时分秒",24,1);
Show_Str(42,148,72,24,"中间以",24,1);	
LCD_ShowString(114,148,12,24,24,"#");
Show_Str(126,148,72,24,"键隔开",24,1);	

	
	}
}






void Interface_Change_Time_Blink(u16* MS_Count,u8 count,u8 interface_code)
{
	if(interface_code==Time_Change_Interface)
	{delay_ms(1);
	++(*MS_Count);
	if(*MS_Count==500)
		LCD_ShowString(count*12,172,240,24,24,"_");
	if(*MS_Count==1000)
	{*MS_Count=0;LCD_ShowString(count*12,172,240,24,24," "); }}
	
}
void Interface_Change_Time_Show(u8 Key_Value,u8 * count,u8 Keyboard_Status,u8 interface_code)
{
	if((interface_code==Time_Change_Interface)&&(Keyboard_Status==Flag_OK))
	{
		if (Key_Value=='z')
		{LCD_ShowString((*count)*12,172,240,24,24," ");
		 --(*count);}
		if((Key_Value!='y')&&(Key_Value!='z'))
		{++(*count);
			if(Key_Value=='#')
		LCD_ShowString((*count)*12-12,172,240,24,24,"#");////////////
				else
					LCD_ShowNum((*count)*12-12,172,(Key_Value-'0'),1,24);
		}	
		if (Key_Value=='y')
		*count=0;	
	}

}

void Get_Time_Change(u8 Key_value ,u8 *IN_Password_P,u8* Flag_End_P,u8 interface_code,u8 Keyboard_Status)
{			
			
			if ((Keyboard_Status == Flag_OK )&&(interface_code==Time_Change_Interface))
				{	
					
					if( Key_value=='y')
					{*Flag_End_P=1;*(IN_Password_P+Get_Password_Count)='\0';Get_Password_Count=0;}
					else if(Key_value=='z')
					{Get_Password_Count--;}
					else	if(Key_value!='#')	
					{*(IN_Password_P+Get_Password_Count)=Key_value-'0'; Get_Password_Count++;}
						else
					{*(IN_Password_P+Get_Password_Count)=Key_value; Get_Password_Count++;}		
				}
				

				
				
}

void Time_Change_Action(u8 interface_code,u8* Flag_End_P)
{
	
if (((*Flag_End_P) == 1 )&&(interface_code==Time_Change_Interface))
{
	*Flag_End_P=0;
	
	syear=timeset[0]*1000+timeset[1]*100+timeset[2]*10+timeset[3];
	smon=timeset[5]*10+timeset[6];
	sday=timeset[8]*10+timeset[9];
	hour=timeset[11]*10+timeset[12];
	min=timeset[14]*10+timeset[15];
	sec=timeset[17]*10+timeset[18];

RTC_Set(syear,smon,sday,hour,min,sec);
LCD_Clear(BLACK);	
Show_Str(72,148,96,24,"修改成功",24,1);
delay_ms(1500);
Step=0;
		Flag_SetInit=1;//进主界面
		Interface_Code_Now=Main_Interface;
		EN_TimesShow=1;
}



}


void Interface_IC_add_del_loop(u8 Keyboard_Status,u8 interface_code)
{
if((interface_code==IC_add_del_Interface)&&(Keyboard_Status==Flag_OK))
{
if (Key_Value=='A')
{Interface_Forward(Interface_Step , &Step,&Interface_Code_Now,IC_add_Interface,&Flag_SetInit);}
if (Key_Value=='B')
{Interface_Forward(Interface_Step , &Step,&Interface_Code_Now,IC_del_Interface,&Flag_SetInit);}
if (Key_Value=='#')
{Interface_Forward(Interface_Step , &Step,&Interface_Code_Now,IC_Verify_Interface,&Flag_SetInit);}



}


}

void Interface_IC_add_Init(u8 *Init,u8 interface_code,u8 IC_User_Count)
{
if((*Init)&&(interface_code==IC_add_Interface))
{
*Init=0;
LCD_Clear(BLACK);
Show_Str(30,136,96,24,"现状已有",24,1);
LCD_ShowNum(126,136,IC_User_Count,1,24);	
Show_Str(138,136,102,24,"张卡片",24,1);
Show_Str(12,160,228,24,"请刷入要添加的卡片",24,1);	

}



}

void Interface_IC_add_loop(u8 interface_code)
	{
if((Get_ucArray_ID(ucArray_ID ,Interface_Code_Now )==MI_OK_Change)&&(interface_code==IC_add_Interface))
{
Add_IC(ucArray_ID,&IC_User_Count);
	LCD_Clear(BLACK);
	Show_Str(72,148,96,24,"添加成功",24,1);
	delay_ms(1500);
		Step=0;
		Flag_SetInit=1;//进主界面
		Interface_Code_Now=Main_Interface;
		EN_TimesShow=1;
}


}

void Interface_IC_del_Init(u8 *Init,u8 interface_code,u8 IC_User_Count)
{
if((*Init)&&(interface_code==IC_del_Interface))
{
*Init=0;
LCD_Clear(BLACK);
Show_Str(30,136,96,24,"现状已有",24,1);
LCD_ShowNum(126,136,IC_User_Count,1,24);	
Show_Str(138,136,102,24,"张卡片",24,1);
Show_Str(48,160,192,24,"请输入要删除",24,1);
Show_Str(60,184,180,24,"的卡片序号",24,1);	
	

}



}
void Interface_IC_del_loop(u8 Keyboard_Status,u8 interface_code)
{
if((interface_code==IC_del_Interface)&&(Keyboard_Status==Flag_OK))
{
del_number=Key_Value-48;
Del_IC(del_number,&IC_User_Count)	;
	LCD_Clear(BLACK);
	Show_Str(72,148,96,24,"删除成功",24,1);
	delay_ms(1500);
		Step=0;
		Flag_SetInit=1;//进主界面
		Interface_Code_Now=Main_Interface;
		EN_TimesShow=1;
}


}


void Add_IC(u8*ucArray_ID,u8*IC_User_Count)
{
W25QXX_Write(ucArray_ID,(FLASH_SIZE-80+(*IC_User_Count)*4),4);
++(*IC_User_Count);
W25QXX_Write(IC_User_Count,FLASH_SIZE-60,1);	
//更新
	W25QXX_Read(IC_User_Count,FLASH_SIZE-60,1);
	W25QXX_Read(IC_Password,FLASH_SIZE-80,20);	
}
void Del_IC(u8 number,u8*IC_User_Count)
{
u8 last=(*IC_User_Count)*4;
u8 start=(number-1)*4;
	u8 count=((last-start)/4)-1;//要移动的组数
	u8 i,j;
	u8 count_other=0;
	for(i=count;i>=1;i--)
	{for(j=0;j<4;j++)
	{IC_Password[(start+4*count_other)+j]=IC_Password[(last-4*i)+j];}
	count_other++;
		}
--(*IC_User_Count);
	W25QXX_Write(IC_Password,FLASH_SIZE-80,20);
	W25QXX_Write(IC_User_Count,FLASH_SIZE-60,1);
}

void Check_FINGER( u8 interface_code)
{ 
 if(interface_code==Main_Interface)
 {
 Check_Finger(&Flag_End);
 }

}


void Interface_Finger_add_del_Verify_Init(u8 *Init,u8 interface_code)
{
if((*Init)&&(interface_code==Finger_add_del_Verify_Interface))
{
*Init=0;
LCD_Clear(BLACK);
LCD_ShowString(54,124,186,24,24,"F1:");
Show_Str(90,124,186,24,"添加指纹",24,1);
LCD_ShowString(54,148,186,24,24,"F2:");
Show_Str(90,148,186,24,"删除指纹",24,1);	
LCD_ShowString(60,172,180,24,24,"#:");
Show_Str(84,172,156,24,"识别指纹",24,1);		

}

}

void Interface_Finger_add_Init(u8 *Init,u8 interface_code)
{
if((*Init)&&(interface_code==Finger_add_Interface))
{
*Init=0;
while(Get_Finger_User_Number(&Finger_User_Count)!=Finger_OK);	
LCD_Clear(BLACK);
Show_Str(30,136,96,24,"现状已有",24,1);
LCD_ShowNum(126,136,Finger_User_Count,1,24);	
Show_Str(138,136,102,24,"个指纹",24,1);
Show_Str(12,160,228,24,"请按下要添加的指纹",24,1);
	Add_Finger();
	

}



}
void Interface_Finger_del_Init(u8 *Init,u8 interface_code)
{
if((*Init)&&(interface_code==Finger_del_Interface))
{
*Init=0;
while(Get_Finger_User_Number(&Finger_User_Count)!=Finger_OK);	
LCD_Clear(BLACK);
Show_Str(30,136,96,24,"现状已有",24,1);
LCD_ShowNum(126,136,Finger_User_Count,1,24);	
Show_Str(138,136,102,24,"个指纹",24,1);
Show_Str(12,160,228,24,"请输入要删除的指纹",24,1);	
	

}


}

void Interface_Finger_del_loop(u8 Keyboard_Status,u8 interface_code)
{
if((interface_code==Finger_del_Interface)&&(Keyboard_Status==Flag_OK))
{	
	u8 Want_Del_NO;
Want_Del_NO=Key_Value-48;
while(Send_CMD_Delete(&Want_Del_NO)!=Finger_OK);
	LCD_Clear(BLACK);
	Show_Str(72,148,96,24,"删除成功",24,1);
	delay_ms(1500);
		Step=0;
		Flag_SetInit=1;//进主界面
		Interface_Code_Now=Main_Interface;
		EN_TimesShow=1;
}


}
void Interface_Finger_Verify_Init(u8 *Init,u8 interface_code)
{
if((*Init)&&(interface_code==Finger_Verify_Interface))
{
*Init=0;
	Time_Out_Count=0;
	
while(Get_Finger_User_Number(&Finger_User_Count)!=Finger_OK);	
LCD_Clear(BLACK);
Show_Str(30,136,96,24,"现状已有",24,1);
LCD_ShowNum(126,136,Finger_User_Count,1,24);	
Show_Str(138,136,102,24,"个指纹",24,1);
Show_Str(12,160,228,24,"请按下要识别的指纹",24,1);
do{Finger_Status=Send_CMD_GET_IMAGE();}while(Finger_Status!=Finger_OK);
do	{Finger_Status=Send_CMD_Create_Target();}
while(Finger_Status!=Finger_OK);
do{Finger_Status=Get_Finger_CodeNum(&Finger_CodeNum);Time_Out_Count++;if(Time_Out_Count==15)break;}while(Finger_Status!=Finger_OK);
if(Time_Out_Count==15) {Time_Out_Count=0;Show_Str(60,184,180,24,"查无此指纹",24,1);}
else {Show_Str(48,184,144,24,"此指纹编号为",24,1);LCD_ShowString(192,184,48,24,24,":");LCD_ShowNum(204,184,Finger_CodeNum,1,24);}


	
}


}
void Interface_Finger_add_del_Verify_loop(u8 Keyboard_Status,u8 interface_code)
{
if((interface_code==Finger_add_del_Verify_Interface)&&(Keyboard_Status==Flag_OK))
{
if (Key_Value=='A')
{Interface_Forward(Interface_Step , &Step,&Interface_Code_Now,Finger_add_Interface,&Flag_SetInit);}
if (Key_Value=='B')
{Interface_Forward(Interface_Step , &Step,&Interface_Code_Now,Finger_del_Interface,&Flag_SetInit);}
if (Key_Value=='#')
{Interface_Forward(Interface_Step , &Step,&Interface_Code_Now,Finger_Verify_Interface,&Flag_SetInit);}

}


}


u8 Get_ucArray_CodeNum(u8 IC_User_Count,u8*ucArray_ID)
{ u8 ii;
	u8 iii;
 
 for(ii=0;ii<IC_User_Count;ii++)
	 {
	 for(iii=0;iii<4;iii++)
		 {
			 if((*(ucArray_ID+iii))!=IC_Password[ii*4+iii])break;
			 if(iii==3) return ii+1 ;
		 }
		 
	 
	 }
 
 
return 0;
}


void Interface_IC_Verify_Init(u8 *Init,u8 interface_code,u8 IC_User_Count)
{
if((*Init)&&(interface_code==IC_Verify_Interface))
{
*Init=0;
LCD_Clear(BLACK);
Show_Str(30,136,96,24,"现在已有",24,1);
LCD_ShowNum(126,136,IC_User_Count,1,24);	
Show_Str(138,136,102,24,"张卡片",24,1);
Show_Str(12,160,228,24,"请刷入要识别的卡片",24,1);	

}



}

void Interface_IC_Verify_loop(u8 interface_code)
	{	
if((Get_ucArray_ID(ucArray_ID ,Interface_Code_Now )==MI_OK_Verify)&&(interface_code==IC_Verify_Interface))
{
	ucArray_CodeNum=Get_ucArray_CodeNum(IC_User_Count,ucArray_ID);
	LCD_Clear(BLACK);
	if(ucArray_CodeNum==0)
	{Show_Str(60,148,180,24,"查无此卡片",24,1);delay_ms(1500);}
	else
	{
	Show_Str(36,148,144,24,"此卡片编号为",24,1);
	LCD_ShowString(180,148,12,24,24,";");	
	LCD_ShowNum(192,148,ucArray_CodeNum,1,24);
	delay_ms(1500);
	}
	
	
}


}

void Home(u8 keyvalue,u8 Keyboard_Status)
{
if((keyvalue=='u')&&(Keyboard_Status==Flag_OK))
{
	Step=0;
		Flag_SetInit=1;//进主界面
		Interface_Code_Now=Main_Interface;
		EN_TimesShow=1;
		//返回主界面
}


}
