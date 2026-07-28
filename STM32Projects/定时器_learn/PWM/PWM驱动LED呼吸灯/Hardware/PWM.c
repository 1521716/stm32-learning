#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	// RCC开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// 选择时钟
	TIM_InternalClockConfig(TIM2);
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_InitBaseStructure;
	TIM_InitBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitBaseStructure.TIM_Period = 100-1;						// ARR
	TIM_InitBaseStructure.TIM_Prescaler = 720-1;					// PSC
	TIM_InitBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_InitBaseStructure);
	
	// 初始化比较单元
	TIM_OCInitTypeDef TIM_OCIInitStructure;
	TIM_OCStructInit(&TIM_OCIInitStructure);
	TIM_OCIInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCIInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCIInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCIInitStructure.TIM_Pulse = 50;								// CCR
	TIM_OC1Init(TIM2,&TIM_OCIInitStructure);
	
	// 开启时钟
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}
