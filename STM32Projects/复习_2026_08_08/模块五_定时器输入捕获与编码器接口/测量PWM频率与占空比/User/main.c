#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "IC.h"
#include "PWM.h"


int main()
{
	PWM_Init();
	OLED_Init();
	IC_Init();
	PWM_SetPrescaler(7200 - 1);
	PWM_SetDuty(60);
	OLED_ShowString(1,1,"Freq:     Hz");
	OLED_ShowString(2,1,"Duty:  %");
	
	
	while(1)
	{
		OLED_ShowNum(1,6,IC_GetFreq(),5);
		OLED_ShowNum(2,6,IC_GetDuty(),2);
	}
}

