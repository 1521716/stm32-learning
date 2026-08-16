#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Watch.h"
#include "PWM_Light.h"

uint8_t Sys_Status = 0;
uint8_t KeyNum;
uint8_t ms = 0,s = 0,m = 0;
uint8_t Light_CCR = 0;


/* 函数声明 */
void Sys_Init(void);
void Sys_GetKeyNum(void);
void Sys_Mode_Menu(void);
void Sys_Mode_Watch(void);
void Sys_Mode_PWM_Light(void);
void Sys_Mode_About(void);
void Sys_SelectMode(void);



int main()
{
	Sys_Init();
	while(1)
	{
		Sys_GetKeyNum();
		Sys_SelectMode();
	}
}

/* 函数定义 */
void Sys_Init(void)
{
	// 初始化
	OLED_Init();
	Key_Init();
	
	// 菜单内容
	OLED_ShowString(1,1,"     System     ");
	OLED_ShowString(2,1,"A:Watch    ");
	OLED_ShowString(3,1,"B:PWM_Light");
	OLED_ShowString(4,1,"C:About    ");
	
	
}

void Sys_GetKeyNum(void)
{
	if(Key1_Flag == 1)
	{
		Key1_Flag = 0;
		Delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
			KeyNum =  1;
		}
	}
	else if(Key2_Flag == 1)
	{
		Key2_Flag = 0;
		Delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
			KeyNum =  2;
		}
	}
	else if(Key3_Flag == 1)
	{
		Key3_Flag = 0;
		Delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) == 0)
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) == 0);
			KeyNum =  3;
		}
	}
}

void Sys_Mode_Menu(void)
{
	OLED_ShowString(1,1,"     System     ");
	OLED_ShowString(2,1,"A:Watch    ");
	OLED_ShowString(3,1,"B:PWM_Light");
	OLED_ShowString(4,1,"C:About    ");
}

void Sys_Mode_Watch(void)
{
	Watch_Init();
	OLED_ShowString(1,1,"     Watch:     ");
	
	OLED_ShowString(2,5,"  :  : ");
	
	while(1)
	{
		KeyNum = 0;
		Sys_GetKeyNum();
		if(KeyNum == 3)
		{
			ms = 0;s = 0;m = 0;
			TIM_Cmd(TIM2,DISABLE);	
			Watch_run_Flag = 0;
			return;
		}
			
		else if(KeyNum == 1)
		{
			if(Watch_run_Flag == 1)
			{
				TIM_Cmd(TIM2,DISABLE);
				Watch_run_Flag = 0;
			}
			else
			{
				TIM_Cmd(TIM2,ENABLE);
				Watch_run_Flag = 1;
			}
		}
		else if(KeyNum == 2)
		{
			ms = 0;s = 0;m = 0;
		}
		if(Watch_Flag == 1)
		{
			Watch_Flag = 0;
			ms++;
			if(ms>=10)
			{
				ms = 0;
				s++;
				if(s>=60)
				{
					s = 0;
					m++;
					if(m>=60)
					{
						m = 0;
					}
				}
			}
		}
		OLED_ShowNum(2,5,m,2);
		OLED_ShowNum(2,8,s,2);
		OLED_ShowNum(2,11,ms,1);
		
	}
}

void Sys_Mode_PWM_Light(void)
{
	PWM_Light_Init();
	OLED_ShowString(1,1,"   PWM_Light:   ");
	OLED_ShowString(2,1,"CCR:   ");
	
	while(1)
	{
		KeyNum = 0;
		Sys_GetKeyNum();
		if(KeyNum == 3)
			return;
		else if(KeyNum == 1)
		{
			Light_CCR+=10;
			if(Light_CCR>=100)	Light_CCR = 100;
		}
		else if(KeyNum == 2)
		{
			if(Light_CCR<=0)	Light_CCR += 10;
			Light_CCR-=10;
			
		}
		PWM_Light_SetCompare1(Light_CCR);
		OLED_ShowNum(2,5,Light_CCR,3);
	}
	
}

void Sys_Mode_About(void)
{
	OLED_ShowString(1,1,"     About:     ");
	OLED_ShowString(2,1,"Author:LiRui");
	OLED_ShowString(3,1,"Date  :     ");
	OLED_ShowString(4,1,"2026-08-15");
}	

void Sys_SelectMode(void)
{
	if(KeyNum == 3)
	{
		OLED_Clear();
		Sys_Status++;
		Sys_Status %= 4;	
		KeyNum = 0;
	}
	if(Sys_Status == 0)
		Sys_Mode_Menu();
	else if(Sys_Status == 1)
		Sys_Mode_Watch();
	else if(Sys_Status == 2)
		Sys_Mode_PWM_Light();
	else if(Sys_Status == 3)
		Sys_Mode_About();
	
}
