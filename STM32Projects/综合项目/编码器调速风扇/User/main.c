#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Motor.h"

int8_t Speed;

int main()
{
	OLED_Init();
	Motor_Init();
	
	OLED_ShowString(1,1,"Speed:");
	
	while(1)
	{
		Speed = Motor_GetSpeed();
		
		OLED_ShowSignedNum(1,7,Speed,3);
		Motor_SetSpeed(Speed);
		
	}
}
