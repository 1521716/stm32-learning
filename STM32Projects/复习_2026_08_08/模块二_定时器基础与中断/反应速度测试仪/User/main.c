#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include <stdlib.h>

uint16_t ms = 0;
uint16_t next_arr = 0;

void Sys_Init(void);

int main()
{
	Sys_Init();
	while(1)
	{
		if(Key1_Flag == 1)
		{
			Key1_Flag = 0;
			next_arr = rand()%30001+20000;
			TIM_SetAutoreload(TIM2,next_arr);
			TIM_Cmd(TIM2,ENABLE);
		}
		if(TIM2_Flag == 1)
		{
			TIM2_Flag = 0;
			LED_SetStatus(0);
			TIM_Cmd(TIM3,ENABLE);
		}
		if(Key2_Flag == 1)
		{
			LED_SetStatus(1);
			Key2_Flag = 0;
			ms = TIM_GetCounter(TIM3);
			TIM_Cmd(TIM2,DISABLE);
			TIM_SetCounter(TIM2,0);
			TIM_Cmd(TIM3,DISABLE);
			TIM_SetCounter(TIM3,0);
			OLED_ShowNum(1,10,ms,4);
		}
		
		
	}
}


void Sys_Init(void)
{
	srand(SysTick->VAL);
	next_arr = 20000;
	
	LED_Init();
	OLED_Init();
	Timer_Init();
	Key_Init();
	
	OLED_ShowString(1,1,"Reaction:    ms");
}
