#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include "LED.h"

uint8_t KeyNum = 0;

int main()
{
	LED_Init();
	Key_Init();
	Timer_Init();
	OLED_Init();
	
	OLED_ShowString(1,1,"Light OFF in: s");
	
	while(1)
	{
		
		if(Flag_Key == 1)
		{
			Flag_Key = 0;
			LED_SetStatus(0);
			TIM_Cmd(TIM2,ENABLE);
			TIM_SetCounter(TIM2,0);
		}
		if(Flag_Timer == 1)
		{
			Flag_Timer = 0;
			TIM_Cmd(TIM2,DISABLE);
			LED_SetStatus(1);
		}
		OLED_ShowNum(1,14,Timer_GetS()/10000,1);
	}
}
