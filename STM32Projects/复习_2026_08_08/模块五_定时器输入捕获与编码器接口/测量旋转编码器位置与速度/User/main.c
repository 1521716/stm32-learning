#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "IC.h"

int16_t LastLocation = 0;

int main()
{
	OLED_Init();
	IC_Init();
	
	OLED_ShowString(1,1,"Location:    ");
	OLED_ShowString(2,1,"Speed   :    ");
	
	
	while(1)
	{
		OLED_ShowSignedNum(1,10,IC_GetLocation(),3);
		OLED_ShowSignedNum(2,10,IC_GetLocation() - LastLocation,2);
		LastLocation = IC_GetLocation();
		Delay_s(1);
		
	}
}

