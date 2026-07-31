#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Motor.h"
#include "AD.h"

uint16_t Speed = 0;

int main()
{
	OLED_Init();
	Key_Init();
	Motor_Init();
	AD_Init();
	
	OLED_ShowString(1,1,"Mode :");
	OLED_ShowString(2,1,"Temp :");
	OLED_ShowString(3,1,"Speed:");
	OLED_ShowString(4,1,"State:");
	
	while(1)
	{
		if(Key1_Flag)
		{
			Key1_Flag = 0;
			Speed+=30;
			Motor_SetSpeed(Speed);
		}
		OLED_ShowNum(3,7,Speed,3);
		OLED_ShowNum(2,7,AD_GetValue(),4);
	}
}
