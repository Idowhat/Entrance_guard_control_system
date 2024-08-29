#ifndef __FINGERPRINT_H
#define __FINGERPRINT_H	
#include "sys.h"
#include "stdint.h"
#define Finger_OK 0x80
#define Finger_ERROR 0x40
#define WakeUp  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)
void Wake_Up_Init(void);
void Send_CMD_init(void);
u8 Send_CMD_GET_IMAGE(void);
u8 Send_CMD_Create_Target(void);
u8 Get_Finger_User_Number(u8*Finger_User);
u8 Send_CMD_Search(void);
u8 Check_Finger(u8*Flag_End);
u8 Send_CMD_Create_Target_To_2(void);
u8 Send_CMD_Create_Target_To_3(void);
u8 Send_CMD_Merge(void);
u8 Send_CMD_Get_usableNO(u8*Usable_NO);
u8 Send_CMD_Get_Storage(u8*Usable_NO);
u8 Send_CMD_Delete(u8*Keyvalue);
void Add_Finger(void);
u8 Get_Finger_CodeNum(u8 *Finger_CodeNum);

#endif
