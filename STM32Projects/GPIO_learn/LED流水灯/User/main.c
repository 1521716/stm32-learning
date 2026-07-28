#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main()
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// GPIO初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;// 用GPIO_Pin_0 | GPIO_Pin_1 | ...  也可以
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	// GPIO初始化
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	while(1)
	{
		static unsigned char i = 0;
		GPIO_Write(GPIOA,~(0x0001<<(i%8)));
		i++;
		Delay_ms(500);
		
	}
}
