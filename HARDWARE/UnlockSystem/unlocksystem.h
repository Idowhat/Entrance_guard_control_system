#ifndef __UNLOCKSYSTEM_H
#define __UNLOCKSYSTEM_H	 
#include "sys.h"
#include "stdlib.h"
//界面码宏定义
#define Main_Interface 0x80
#define PassWord_Interface 0xE0
#define Management_Interface 0xC0
#define Finger_add_del_Verify_Interface 0xFF
#define Finger_add_Interface 0x00
#define Finger_del_Interface 0x01
#define Finger_Verify_Interface 0x03

#define Time_Change_Interface 0x04

#define IC_add_del_Interface 0xF8
#define IC_add_Interface 0xFC
#define IC_del_Interface 0xFE
#define IC_Verify_Interface 0x07
#define PassWord_Interface_Change 0xF0
void Interface_Back(u8*array,u8*step,u8*Interface_Code_Now_p,u8 *enable,u8 *Init);
void Interface_Main(u8 *TimeEnable,u8 *Init,u8 interface_code);
void Interface_PassWord_Init(u8 *Init,u8 *TimeEnable,u16* MS_Count,u8 interface_code,u8 * count);
void Interface_PassWord_loop_Blink(u16* MS_Count,u8 count,u8 interface_code);
void Interface_PassWord_loop_Show(u8 Key_Value,u8 * count,u8 Keyboard_Status,u8 interface_code);
void Interface_Forward(u8*array,u8*step,u8*Interface_Code_Now_p,u8 interface_code,u8*Init_p);
void Get_Password(u8 Key_value ,u8 *IN_Password_P,u8* Flag_End_P,u8 interface_code,u8 Keyboard_Status);
void Time_Auto_Show(u8* t_P,u8 enable);
void Interface_Management_Init(u8 *Init,u8 interface_code);
void Interface_Management_loop(u8 Keyboard_Status,u8 interface_code);
void Check_ucArray_ID(u8 IC_Status,u8 IC_User_Count,u8*Flag_End,u8*ucArray_ID);

void Interface_IC_add_del_Init(u8 *Init,u8 interface_code);
void Interface_IC_add_del_loop(u8 Keyboard_Status,u8 interface_code);
void Interface_IC_add_Init(u8 *Init,u8 interface_code,u8 IC_User_Count);
void Interface_IC_add_loop(u8 interface_code);
void Interface_IC_del_Init(u8 *Init,u8 interface_code,u8 IC_User_Count);
void Interface_IC_del_loop(u8 Keyboard_Status,u8 interface_code);
void Add_IC(u8*ucArray_ID,u8*IC_User_Count);
void Del_IC(u8 number,u8*IC_User_Count);

void Check_FINGER( u8 interface_code);
void Interface_Finger_add_del_Verify_Init(u8 *Init,u8 interface_code);
void Interface_Finger_add_Init(u8 *Init,u8 interface_code);
void Interface_Finger_del_Init(u8 *Init,u8 interface_code);
void Interface_Finger_del_loop(u8 Keyboard_Status,u8 interface_code);
void Interface_Finger_Verify_Init(u8 *Init,u8 interface_code);
void Interface_Finger_add_del_Verify_loop(u8 Keyboard_Status,u8 interface_code);
void ESC(u8 keyvalue,u8 Keyboard_Status);
void Home(u8 keyvalue,u8 Keyboard_Status);

u8 Get_ucArray_CodeNum(u8 IC_User_Count,u8*ucArray_ID);
void Interface_IC_Verify_Init(u8 *Init,u8 interface_code,u8 IC_User_Count);
void Interface_IC_Verify_loop(u8 interface_code);

void Interface_Change_Time_Init(u8 *Init,u16* MS_Count,u8 interface_code,u8 * count);
void Interface_Change_Time_Blink(u16* MS_Count,u8 count,u8 interface_code);
void Interface_Change_Time_Show(u8 Key_Value,u8 * count,u8 Keyboard_Status,u8 interface_code);
void Get_Time_Change(u8 Key_value ,u8 *IN_Password_P,u8* Flag_End_P,u8 interface_code,u8 Keyboard_Status);
void Time_Change_Action(u8 interface_code,u8* Flag_End_P);


#endif
