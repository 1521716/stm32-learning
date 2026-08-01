#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint32_t Cnt_Mode = 0,Cnt_Speed = 0;

void LED_Init(void)
{
	// RCC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
}

void LED1_Mode_AUTO(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}
void LED1_Mode_MANUAL(void)
{
	Cnt_Mode++;
	if(Cnt_Mode>=20)
	{
		Cnt_Mode = 0;
		GPIO_WriteBit(GPIOC, GPIO_Pin_13,
              (BitAction)!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13));
	}
}
void LED2_Speed(uint8_t index)
{
	if(index == 1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_15);
	}
	else if(index == 2)
	{
		
		Cnt_Speed++;
		if(Cnt_Speed>=20)
		{
			Cnt_Speed = 0;
			GPIO_WriteBit(GPIOC, GPIO_Pin_15,
				  (BitAction)!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_15));
		}
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_15);
	}
}
