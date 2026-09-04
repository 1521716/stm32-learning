#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "USART.h"
#include "Key.h"
#include "LED.h"
#include <string.h>

void Sys_Init(void);
void Sys_Task(void);

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
	Key_Init();
	LED_Init();
	
	
	OLED_ShowString(1,1,"TxPacket:");
	OLED_ShowString(3,1,"RxPacket:");
	
}

void Sys_Task(void)
{
	if(MyUSART_GetRxFlag() == 1)
	{
		OLED_ShowString(4,1,"                ");
		OLED_ShowString(4,1,RxPacket);
		
		if(strcmp(RxPacket,"LED_ON") == 0)
		{
			LED1_ON();
			MyUSART_SendString("LED_ON_OK\r\n");
			OLED_ShowString(2,1,"                ");
			OLED_ShowString(2,1,"LED_ON_OK");
		}
		else if(strcmp(RxPacket,"LED_OFF") == 0)
		{
			LED1_OFF();
			MyUSART_SendString("LED_OFF_OK\r\n");
			OLED_ShowString(2,1,"                ");
			OLED_ShowString(2,1,"LED_OFF_OK");
		}
		else
		{
			MyUSART_SendString("ERROR_COMMAND\r\n");
			OLED_ShowString(2,1,"                ");
			OLED_ShowString(2,1,"ERROR_COMMAND");
		}
	}
}
