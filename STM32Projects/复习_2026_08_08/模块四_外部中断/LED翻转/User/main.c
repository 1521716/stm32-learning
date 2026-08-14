#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Key.h"
#include "LED.h"

uint8_t KeyNum = 0;
uint8_t State = 0;

int main()
{
	LED_Init();
	Key_Init();
	
	while(1)
	{
		KeyNum = Key_GetKeyNum();
		
		if(KeyNum == 1)
		{
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == RESET)
			{
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == RESET);
				LED1_TurnStatus();
			}
		}
		if(KeyNum == 2)
		{
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == RESET)
			{
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == RESET);
				LED2_TurnStatus();
			}
		}
	}
}
