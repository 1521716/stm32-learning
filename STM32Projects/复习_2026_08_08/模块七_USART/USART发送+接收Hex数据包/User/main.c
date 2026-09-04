#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "USART.h"
#include "Key.h"

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
	
	TxPacket[0] = 0x01;
	TxPacket[1] = 0x02;
	TxPacket[2] = 0x03;
	TxPacket[3] = 0x04;
	
	OLED_ShowString(1,1,"TxPacket:");
	OLED_ShowString(3,1,"RxPacket:");
	
}

void Sys_Task(void)
{
	if(Key_GetFlag() == 1)
	{
		TxPacket[0]++;
		TxPacket[1]++;
		TxPacket[2]++;
		TxPacket[3]++;
		
		MyUSART_SendPacket();
		
		OLED_ShowHexNum(2,1,TxPacket[0],2);
		OLED_ShowHexNum(2,4,TxPacket[1],2);
		OLED_ShowHexNum(2,7,TxPacket[2],2);
		OLED_ShowHexNum(2,10,TxPacket[3],2);
	}
	if(MyUSART_GetRxFlag() == 1)
	{
		OLED_ShowHexNum(4,1,RxPacket[0],2);
		OLED_ShowHexNum(4,4,RxPacket[1],2);
		OLED_ShowHexNum(4,7,RxPacket[2],2);
		OLED_ShowHexNum(4,10,RxPacket[3],2);
	}
}
