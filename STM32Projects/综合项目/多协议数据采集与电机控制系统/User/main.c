#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Key.h"

uint8_t KeyNum;

int main()
{
	OLED_Init();
	Key_Init();
	
	while(1)
	{
		KeyNum = Key_GetKeyNum();
		
		OLED_ShowNum(1,1,KeyNum,2);
		
	}
}
