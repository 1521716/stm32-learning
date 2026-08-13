#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"
#include "Timer.h"

uint8_t LED1_i = 0,LED2_i = 0;
uint8_t LED1_t = 0,LED2_t = 0;
uint8_t LED1_Flag = 0,LED2_Flag = 0;
uint8_t div = 0;


int main()
{
	PWM_Init();
	Timer_Init();

	while(1)
	{
		if(LED_Flag == 1)          
		{
			LED_Flag = 0;

			if(LED1_t == 0)
			{
				LED1_i++;
				if(LED1_i >= 100) LED1_t = 1;
			}
			else
			{
				LED1_i--;
				if(LED1_i == 0)   LED1_t = 0;
			}
			PWM_SetCompare1(LED1_i);

			div = !div;
			if(div == 0)
			{
				if(LED2_t == 0)
				{
					LED2_i++;
					if(LED2_i >= 100) LED2_t = 1;
				}
				else
				{
					LED2_i--;
					if(LED2_i == 0)   LED2_t = 0;
				}
				PWM_SetCompare2(LED2_i);
			}
		}
	}
}
