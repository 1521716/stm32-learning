#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main()
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// GPIO初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	// GPIO初始化
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/*
	// 给指定端口配置低电平
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	
	// 给指定端口配置高电平
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	
	// 通过GPIO_WriteBit配置高低电平
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);			// Bit_RESET=0;Bit_SET=1;
	*/
	
	while(1)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
		Delay_ms(500);
	}
}
