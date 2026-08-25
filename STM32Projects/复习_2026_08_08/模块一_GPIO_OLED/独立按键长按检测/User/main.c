#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include "LED.h"

uint8_t Key2_Status = 0;

int main()
{
	LED_Init();
	Key_Init();
	Timer_Init();
	
	LED2_TurnStatus();
	
	while(1)
	{
		if(Flag_Key1 == 1)
		{
			Flag_Key1 = 0;
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == RESET)
			{
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == RESET);
				LED1_TurnStatus();
			}
		}
		if(Flag_Key2 == 1)
		{
			Flag_Key2 = 0;
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == RESET)
			{
				if(Key2_Status == 0)
				{
					Key2_Status = 1;
					TIM_Cmd(TIM2,ENABLE);
				}
			}
			else
			{
				if(Key2_Status == 1)
				{
					Key2_Status = 0;
					TIM_Cmd(TIM2,DISABLE);
					TIM_SetCounter(TIM2,0);
				}
			}
			
		}
		if(Flag_Timer == 1 && Key2_Status == 0)
		{
			Flag_Timer = 0;
			LED2_TurnStatus();
		}
		
	}
}
