#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Timer.h"

uint8_t Flag = 0,State = 0;


void Sys_Init(void);

int main()
{
	Sys_Init();
	while(1)
	{
		Flag = Timer_GetFlag();
		if(Flag == 1)
		{
			State = ~State;
			LED_SetStatus(State);
		}
	}
}


void Sys_Init(void)
{
	LED_Init();
	Timer_Init();
}
