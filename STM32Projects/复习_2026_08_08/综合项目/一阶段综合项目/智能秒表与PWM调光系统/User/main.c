#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Watch.h"

uint8_t KeyNum;
uint8_t ms = 0,s = 0,m = 0;

/* 函数声明 */
uint8_t Sys_GetKeyNum();


int main()
{
	Watch_Init();
	OLED_Init();
	OLED_ShowString(1,1,"  :  : ");
	/*
	OLED_ShowString(1,1,"     System     ");
	OLED_ShowString(2,1,"A:Watch    ");
	OLED_ShowString(3,1,"B:PWM_Light");
	OLED_ShowString(4,1,"C:About    ");*/
	
	while(1)
	{
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
		OLED_ShowNum(1,1,m,2);
		OLED_ShowNum(1,4,s,2);
		OLED_ShowNum(1,7,ms,1);
	}
}

/* 函数定义 */
uint8_t Sys_GetKeyNum()
{
	if()
}
