#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"

uint8_t Num = 0;

int main()
{
	LED_Init();
	
	while(1)
	{
		Num++;
		LED_SetStatus(~Num);
		Delay_ms(500);
	}
}
