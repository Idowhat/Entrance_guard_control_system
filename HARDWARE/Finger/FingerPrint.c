#include "FingerPrint.h"
#include "unlocksystem.h"
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "stdint.h"
#include "lcd.h"
#include "text.h"
//测试
/*extern u8 flag_add;
extern u8 Flag_End;
extern u8 flag_del;
u8 Want_Del_NO=3;*/
//
u8 Finger_User_Count;
u8 SendCMD[26];
u8 Receive_Data[26];
u8 Time_Out_Count=0;
u8 Usable_NO;
	u8 a=0;
	extern u8 Finger_Status;
	extern u8 Flag_Receive_Finish;
	extern u8 Step;
	extern u8 Flag_SetInit;
	extern u8 Interface_Code_Now;
	extern u8 EN_TimesShow;
	void Wake_Up_Init(void)
	{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	}
void Send_CMD_init(void)
{
SendCMD[0]=0x55;
SendCMD[1]=0xAA;
for(a=2;a<26;a++)
SendCMD[a]=0x00;
}
u8 Send_CMD_GET_IMAGE(void)
{	
	SendCMD[4]=0x20;
	SendCMD[5]=0x00;
	SendCMD[6]=0x00;
	SendCMD[7]=0x00;
	SendCMD[24]=0x1F;
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
return Finger_OK;
else
return	Finger_ERROR;
}

u8 Send_CMD_Create_Target(void)
{	
	SendCMD[4]=0x60;
	SendCMD[5]=0x00;
	SendCMD[6]=0x02;
	SendCMD[7]=0x00;
	SendCMD[24]=0x61;
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
return Finger_OK;
else
return	Finger_ERROR;
}
u8 Get_Finger_User_Number(u8*Finger_User)
{
	SendCMD[4]=0x48;
	SendCMD[5]=0x00;
	SendCMD[6]=0x04;
	SendCMD[7]=0x00;
	SendCMD[8]=0x01;
	SendCMD[9]=0x00;
	SendCMD[10]=0x0A;
	SendCMD[11]=0x00;
	SendCMD[24]=0x56;
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
	SendCMD[8]=0x00;
	SendCMD[9]=0x00;
	SendCMD[10]=0x00;
	SendCMD[11]=0x00;
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
{*Finger_User=Receive_Data[10];return Finger_OK;}
else
return	Finger_ERROR;

}

u8 Send_CMD_Search(void)
{	
	SendCMD[4]=0x63;
	SendCMD[5]=0x00;
	SendCMD[6]=0x06;
	SendCMD[7]=0x00;
	
	SendCMD[8]=0x00;
	SendCMD[9]=0x00;
	SendCMD[10]=0x01;
	SendCMD[11]=0x00;
	SendCMD[12]=0x0A;
	SendCMD[13]=0x00;
	
	SendCMD[24]=0x73;
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
SendCMD[10]=0x00;
SendCMD[12]=0x00;
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
return Finger_OK;
else
return	Finger_ERROR;
}

u8 Check_Finger(u8*Flag_End)
{
if(WakeUp==1)
{
Time_Out_Count=0;
	do{Finger_Status=Send_CMD_GET_IMAGE();}
while(Finger_Status!=Finger_OK);
	do	{Finger_Status=Send_CMD_Create_Target();}
while(Finger_Status!=Finger_OK);
	do{Finger_Status=Send_CMD_Search();Time_Out_Count++;if(Time_Out_Count==15)break;}
while(Finger_Status!=Finger_OK);
if(Time_Out_Count==15) {Time_Out_Count=0;return 0;}
*Flag_End=3;
return 1;
}
return 0;
}


u8 Send_CMD_Create_Target_To_2(void)
{	
	SendCMD[4]=0x60;
	SendCMD[5]=0x00;
	SendCMD[6]=0x02;
	SendCMD[7]=0x00;
	SendCMD[8]=0x01;
	SendCMD[24]=0x62;
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
SendCMD[8]=0x00;
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
return Finger_OK;
else
return	Finger_ERROR;
}

u8 Send_CMD_Create_Target_To_3(void)
{	
	SendCMD[4]=0x60;
	SendCMD[5]=0x00;
	SendCMD[6]=0x02;
	SendCMD[7]=0x00;
	SendCMD[8]=0x02;
	SendCMD[24]=0x63;
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
SendCMD[8]=0x00;
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
return Finger_OK;
else
return	Finger_ERROR;
}

u8 Send_CMD_Merge(void)
{	
	SendCMD[4]=0x61;
	SendCMD[5]=0x00;
	SendCMD[6]=0x03;
	SendCMD[7]=0x00;
	SendCMD[10]=0x03;
	SendCMD[24]=0x66;
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
SendCMD[10]=0x00;
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
return Finger_OK;
else
return	Finger_ERROR;
}

u8 Send_CMD_Get_usableNO(u8*Usable_NO)
{	
	SendCMD[4]=0x45;
	SendCMD[5]=0x00;
	SendCMD[6]=0x04;
	SendCMD[7]=0x00;
	SendCMD[8]=0x01;
	SendCMD[10]=0x0A;
	SendCMD[24]=0x53;
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
SendCMD[8]=0x00;
SendCMD[10]=0x00;
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
{*Usable_NO=Receive_Data[10];return Finger_OK;}
else
return	Finger_ERROR;
}

u8 Send_CMD_Get_Storage(u8*Usable_NO)
{	
	SendCMD[4]=0x40;
	SendCMD[5]=0x00;
	SendCMD[6]=0x04;
	SendCMD[7]=0x00;
	SendCMD[8]=(*Usable_NO);
	SendCMD[24]=0x43+(*Usable_NO);
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
SendCMD[8]=0x00;
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
{*Usable_NO=Receive_Data[10];return Finger_OK;}
else
return	Finger_ERROR;
}

u8 Send_CMD_Delete(u8*Keyvalue)
{	
	SendCMD[4]=0x44;
	SendCMD[5]=0x00;
	SendCMD[6]=0x04;
	SendCMD[7]=0x00;
	SendCMD[8]=(*Keyvalue);
	SendCMD[10]=(*Keyvalue);
	SendCMD[24]=0x47+(*Keyvalue)*2;
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
SendCMD[8]=0x00;
SendCMD[10]=0x00;
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
{return Finger_OK;}
else
return	Finger_ERROR;
}
void Add_Finger(void)
{
	
	 
	while(Send_CMD_GET_IMAGE()!=Finger_OK);	while(Send_CMD_Create_Target()!=Finger_OK);//LCD_ShowString(12,160,228,24,24,"                  ");Show_Str(36,160,204,24,"请再次按下手指",24,1);//第一次录入，放图片显示
	while(Send_CMD_GET_IMAGE()!=Finger_OK);	while(Send_CMD_Create_Target_To_2()!=Finger_OK);//LCD_ShowString(12,160,228,24,24,"                  ");Show_Str(12,160,228,24,"请最后一次按下手指",24,1);
	while(Send_CMD_GET_IMAGE()!=Finger_OK);	while(Send_CMD_Create_Target_To_3()!=Finger_OK);
	while(Send_CMD_Merge()!=Finger_OK);while(Send_CMD_Get_usableNO(&Usable_NO)!=Finger_OK);
	while(Send_CMD_Get_Storage(&Usable_NO)!=Finger_OK);	LCD_Clear(BLACK);
	Show_Str(72,148,96,24,"录入成功",24,1);
	delay_ms(1500);
		Step=0;
		Flag_SetInit=1;//进主界面
		Interface_Code_Now=Main_Interface;
		EN_TimesShow=1;
		//表示录入成功
	


}

u8 Get_Finger_CodeNum(u8 *Finger_CodeNum)
{	
	SendCMD[4]=0x63;
	SendCMD[5]=0x00;
	SendCMD[6]=0x06;
	SendCMD[7]=0x00;
	
	SendCMD[8]=0x00;
	SendCMD[9]=0x00;
	SendCMD[10]=0x01;
	SendCMD[11]=0x00;
	SendCMD[12]=0x0A;
	SendCMD[13]=0x00;
	
	SendCMD[24]=0x73;
	SendCMD[25]=0x01;
for (a=0;a<26;a++)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_SendData(USART1,SendCMD[a]);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

}
SendCMD[10]=0x00;
SendCMD[12]=0x00;
while(Flag_Receive_Finish!=1);
Flag_Receive_Finish=0;
if((Receive_Data[8]==0x00)&&(Receive_Data[9]==0x00))
{*Finger_CodeNum=Receive_Data[10];return Finger_OK;}
else
return	Finger_ERROR;
}
