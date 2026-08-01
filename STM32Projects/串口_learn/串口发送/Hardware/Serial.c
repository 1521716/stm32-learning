#include "stm32f10x.h"                  // Device header
#include "stdio.h"

/**
  * @brief  串口发送初始化（USART1）
  * @param  无
  * @retval  无
  */
void Serial_Init(void)
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
	
	// 初始化USART
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	// 使能
	USART_Cmd(USART1,ENABLE);
}

/**
  * @brief  发送一个字节数据
  * @param  Byte 要发送的字节
  * @retval  无
  */
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

/**
  * @brief  发送一个数组
  * @param  *Array 要发送的数组的地址
  * @param  Length 要发送的数组的大小
  * @retval  无
  */
void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i = 0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}

/**
  * @brief  发送一个字符串
  * @param  *String 要发送的字符串地址
  * @retval  无
  */
void Serial_SendString(char *String)
{
	uint16_t i = 0;
	while(String[i] != '\0')
	{
		Serial_SendByte(String[i]);
		i++;
	}
}

/**
  * @brief  获取X的Y次方
  * @param  X 底数
  * @param  Y 指数
  * @retval  结果
  */
uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result = 1;
	while(Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  发送整数
  * @param  Number 要发送的整数
  * @param  Length 发送的整数的位数
  * @retval  无
  */
void Serial_SendNumber(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for(i = 0;i<Length;i++)
	{
		Serial_SendByte((Number / Serial_Pow(10,Length - i - 1) % 10) + '0');
	}
}
	
/**
  * @brief  printf重定向到串口
  * @param  
  * @retval  
  */
int fputc(int ch,FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}
