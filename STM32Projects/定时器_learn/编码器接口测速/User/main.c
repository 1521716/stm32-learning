#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"

int16_t Speed;
int16_t Pos;

int main()
{
	OLED_Init();
	Timer_Init();
	Encoder_Init();
	
	OLED_ShowString(1,1,"Pos  :");
	OLED_ShowString(2,1,"Speed:");
	while(1)
	{
		OLED_ShowSignedNum(1,7,Pos,5);
		OLED_ShowSignedNum(2,7,Speed,5);
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		
		Speed = Encoder_GetPos()-Pos;
		Pos = Encoder_GetPos();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
