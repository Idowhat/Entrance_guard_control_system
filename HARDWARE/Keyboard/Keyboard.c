#include "Keyboard.h"

unsigned char keysta[5][4]={  {1,1,1,1,},{1,1,1,1,},{1,1,1,1,},{1,1,1,1,},{1,1,1,1,}  };
unsigned char backup[5][4]={  {1,1,1,1,},{1,1,1,1,},{1,1,1,1,},{1,1,1,1,},{1,1,1,1,}  };
		unsigned char transform[5][4]={
		{'A','B','#','*'},{'1','2','3','u'},{'4','5','6','d'},{'7','8','9','b'},{'z','0','r','y'}
		};

void Keyboard_Init(void)
{
GPIO_InitTypeDef  GPIO_InitKeyboard;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOG, ENABLE);
	
 GPIO_InitKeyboard.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;				
 GPIO_InitKeyboard.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 GPIO_InitKeyboard.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_Init(GPIOC, &GPIO_InitKeyboard);				
 GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);	

	GPIO_InitKeyboard.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitKeyboard.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitKeyboard);
	
	GPIO_InitKeyboard.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitKeyboard.GPIO_Pin=GPIO_Pin_15;
	GPIO_Init(GPIOG, &GPIO_InitKeyboard);

}

u8 Keyboard_Scanf (u8 *Key_Value)
{
u8 i,j;
	u8 Flag_Action=0;
	for(i=0;i<5;i++)
	{
		for(j=0;j<4;j++)
		{
			if(backup[i][j]!=keysta[i][j])
			{
					if(backup[i][j]!=0)
					{
						*Key_Value=transform[i][j];
						Flag_Action=1;
							
					}
					backup[i][j]=keysta[i][j];
					
			}
			
		}
	
	}
	if (Flag_Action==1)
	return Flag_OK;
	else	
	return Flag_ERROR;
}
