#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Key.h"

uint8_t KeyNum = 0,Timer_Flag = 0;
uint8_t ms = 0,s = 0,m = 0;
uint8_t State = 0;

void Sys_Init(void);
void Sys_Task(void);

int main()
{
	Sys_Init();
	while(1)
	{
		Sys_Task();
	}
}


void Sys_Init(void)
{
	OLED_Init();
	Timer_Init();
	Key_Init();
	
	OLED_ShowString(1,1,"STOPWATCH");
	OLED_ShowString(2,1,"  :  : ");
}

void Sys_Task(void)
{
	Timer_Flag = Timer_GetFlag();
	KeyNum = Key_GetFlag();
	if(State == 0)
	{
		if(KeyNum == 1)	
		{
			Delay_ms(20);
			while(Key_GetFlag() == 1);
			State = 1;
		}	
	}
	else if(State == 1)
	{
		if(Timer_Flag == 1)
		{
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
		if(KeyNum == 1)	
		{
			Delay_ms(20);
			while(Key_GetFlag() == 1);
			State = 2;
		}	
	}
	else if(State == 2)
	{
		if(KeyNum == 1)	
		{
			Delay_ms(20);
			while(Key_GetFlag() == 1);
			State = 3;
		}	
	}
	else if(State == 3)
	{
		ms = 0;s = 0;m = 0;
		State = 0;
	}
	OLED_ShowNum(2,1,m,2);
	OLED_ShowNum(2,4,s,2);
	OLED_ShowNum(2,7,ms,1);
}
