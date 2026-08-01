#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main()
{
	OLED_Init();
	Serial_Init();
	
	OLED_ShowString(1,1,"RxData:");
	while(1)
	{
		/* 查询法接收数据，一般不用，占CPU */
		/*
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)
		{
			RxData = USART_ReceiveData(USART1);
			OLED_ShowHexNum(1,1,RxData,2);
		}
		*/
		
		/* 中断法 */
		if(Serial_RxFlag)
		{
			Serial_RxFlag = 0;
			RxData = Serial_RxData;
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1,8,RxData,2);
		}
	}
}
