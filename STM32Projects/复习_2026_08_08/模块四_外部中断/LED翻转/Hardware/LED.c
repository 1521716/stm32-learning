#include "stm32f10x.h"                  // Device header

/**
  * @brief  LED初始化
  * @param  无
  * @retval  无
  */
void LED_Init(void)
{
	// RCC开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// 初始全灭
	GPIO_Write(GPIOA,0xFF);
}

/**
  * @brief  翻转LED1
  * @param  无
  * @retval  无
  */
void LED1_TurnStatus(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0) == SET)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
	}
}

/**
  * @brief  翻转LED2
  * @param  无
  * @retval  无
  */
void LED2_TurnStatus(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == SET)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
}
