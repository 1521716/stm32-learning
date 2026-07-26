#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

int16_t Num;

int main()
{
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1,1,"Num:");
	
	while(1)
	{
		if(Key1_Flag)
		{
			Key1_Flag = 0;
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)
			{
				Num++;
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0);
				Delay_ms(20);
			}
			
		}
		if(Key2_Flag)
		{
			Key2_Flag = 0;
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == 0)
			{
				Num--;
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == 0);
				Delay_ms(20);
			}
			
		}
		OLED_ShowSignedNum(1,5,Num,5);
	}
}
