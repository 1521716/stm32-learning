#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

uint8_t KeyNum;

int main()
{
	OLED_Init();
	
	while(1)
	{
		OLED_ShowChar(1,1,'A');
		OLED_ShowString(1,3,"Helloworld!");
		OLED_ShowNum(2,1,12345,5);
		OLED_ShowSignedNum(2,7,-66,2);
		OLED_ShowHexNum(3,1,0xAA55,4);
		OLED_ShowBinNum(4,1,0xAA55,16);
		Delay_ms(1000);
		OLED_Clear();
		Delay_ms(1000);
	}
}
