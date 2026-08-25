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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// 初始全灭
	GPIO_Write(GPIOA,0xFF);
}

/**
  * @brief  翻转LED1状态
  * @param  无
  * @retval  无
  */
void LED1_TurnStatus()
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(!GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0)));

}
	
/**
  * @brief  翻转LED2状态
  * @param  无
  * @retval  无
  */
void LED2_TurnStatus()
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_6,(BitAction)(!GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_6)));
}

