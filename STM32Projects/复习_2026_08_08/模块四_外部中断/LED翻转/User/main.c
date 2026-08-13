#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Key.h"
#include "LED.h"

uint8_t KeyNum = 0,Timer_Flag = 0;
uint8_t ms = 0,s = 0,m = 0;
uint8_t State = 0;

void Sys_Init(void);
void Sys_Task(void);

int main()
{
	LED_Init();
	Key_Init();
	
	while(1)
	{
		
	}
}
