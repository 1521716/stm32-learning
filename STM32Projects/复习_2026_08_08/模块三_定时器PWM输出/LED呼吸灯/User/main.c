#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"

int main()
{
	PWM_Init();
	
	while(1)
	{
		uint8_t i;
		for(i = 0;i<100;i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for(i = 100;i>0;i--)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
	}
}
