#include "stm32f10x.h"                  // Device header
#include <stdio.h>

char receive_buf[30];
uint8_t receive_index = 0;
uint8_t cmd_Flag = 0;

void MyUSART_Init(void)
{
	// RCC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// 串口初始化
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}

void MyUSART_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) != SET);
}

void MyUSART_SendArray(uint8_t *Array,uint16_t Count)
{
	uint16_t i;
	for(i = 0;i<Count;i++)
	{
		MyUSART_SendByte(Array[i]);
	}
}

void MyUSART_SendString(char* String)
{
	uint16_t i = 0;
	while(String[i] != '\0')
	{
		MyUSART_SendByte(String[i]);
		i++;
	}
}

int fputc(int ch, FILE *f)
{
	MyUSART_SendByte(ch);			//将printf的底层重定向到自己的发送字节函数
	return ch;
}

void USART1_IRQHandler(void)
{
	uint16_t ch;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		ch = USART_ReceiveData(USART1);
		
		if(ch == '\r' || ch == '\n')
		{
			receive_buf[receive_index] = '\0';
			receive_index = 0;
			cmd_Flag = 1;
		}
		else
		{
			receive_buf[receive_index] = ch;
			receive_index++;
			if(receive_index>=29)	
			{
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);
				return;
			}
		}
	}
	// 清除溢出错误，否则会死循环
    if(USART_GetFlagStatus(USART1, USART_FLAG_ORE) == SET)
    {
        USART_ReceiveData(USART1);  // 读一次DR，清除ORE
    }
	
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	
}
