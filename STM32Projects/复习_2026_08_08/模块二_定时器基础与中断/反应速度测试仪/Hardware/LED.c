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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// 初始全灭
	GPIO_Write(GPIOA,0xFF);
}

/**
  * @brief  控制LED亮灭
  * @param  ByteValue 亮或灭，0=灭，1=亮
  * @retval  无
  */
void LED_SetStatus(BitAction ByteValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,ByteValue);
}


