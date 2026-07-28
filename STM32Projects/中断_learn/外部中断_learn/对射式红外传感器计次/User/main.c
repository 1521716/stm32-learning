#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

int main()
{
	OLED_Init();
	CountSensor_Init();
	
	OLED_ShowString(1,1,"Count:");
	
	while(1)
	{
		if(CountSensor_GetFlag())
		{
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == 0)
			{
				CountSensor_Count++;
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == 0);
			}
			CountSensor_Flag = 0;
		}
		OLED_ShowNum(1,7,CountSensor_Count,5);
	}
}
