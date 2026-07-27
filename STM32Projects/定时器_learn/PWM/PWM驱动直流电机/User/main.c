#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"

uint8_t Speed;

int main()
{
	OLED_Init();
	Motor_Init();
	
	Motor_SetSpeed(100);
	
	while(1)
	{
		
	}
}
