#include "stm32f10x.h"                  // Device header

/**
  * @brief  Key初始化
  * @param  无
  * @retval  无
  */
void Key_Init(void)
{
	// RCC开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

/**
  * @brief  获取键码
  * @param  无
  * @retval  键码
  */
uint8_t Key_GetKeyNum(void)
{
	uint8_t KeyNum = 0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == RESET)
	{
		KeyNum = 1;
	}
	return KeyNum;
}
