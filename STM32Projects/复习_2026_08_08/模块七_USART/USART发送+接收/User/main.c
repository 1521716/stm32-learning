#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "USART.h"

void Sys_Init(void);
void Sys_Task(void);

uint8_t Array[4] = {0x01,0x02,0x03,0x04};
char String[] = "PrintString";
uint8_t RxData;
int main()
{
	
	
	Sys_Init();
	
	while(1)
	{
		Sys_Task();
	}
}


void Sys_Init(void)
{
	OLED_Init();
	MyUSART_Init();
	
	OLED_ShowString(1,1,"RxData:");
}

void Sys_Task(void)
{
	if(MyUSART_GetRxFlag() == 1)
	{
		RxData = MyUSART_GetRxData();
		MyUSART_SendByte(RxData);
		OLED_ShowHexNum(1,8,RxData,2);
	}
}
