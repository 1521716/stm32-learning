#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "MyI2C.h"
#include "OLED.h"

int main()
{
	OLED_Init();
	MyI2C_Init();
	
	MyI2C_Start();
	MyI2C_SendByte(0xD0);
	uint8_t Ack = MyI2C_ReceiveAck();
	MyI2C_Stop();
	
	OLED_ShowNum(1,1,Ack,3);
	
	while(1)
	{
		
	}
}
