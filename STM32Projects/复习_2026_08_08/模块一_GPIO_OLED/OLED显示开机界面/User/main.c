#include "stm32f10x.h"                  // Device header
#include "OLED.h"

void Sys_Init(void);

int main()
{
	Sys_Init();
	while(1)
	{
	
	}
}


void Sys_Init(void)
{
	OLED_Init();
	
	OLED_ShowString(1,1,"STM32F103C8");
	OLED_ShowString(2,1,"72MHz");
	OLED_ShowString(3,1,"1521716");
}
