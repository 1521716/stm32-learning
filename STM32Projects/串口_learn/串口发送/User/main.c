#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t KeyNum;

int main()
{
	OLED_Init();
	Serial_Init();
	
	
	
	//uint8_t Array[4] = {0x01,0x02,0x11,0x12};
	//Serial_SendArray(Array,4);
	
	//Serial_SendString("Hello World!\r\n");
	
	//Serial_SendByte(0x41);
	
	//Serial_SendNumber(12345,5);
	
	//printf("Num = %d\r\n",666);
	
	printf("你好，世界");
	while(1)
	{
		
	}
}
