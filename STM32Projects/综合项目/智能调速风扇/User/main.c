#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Motor.h"
#include "AD.h"
#include "IR.h"
#include "LED.h"

/***************** 系统变量 *****************/
uint16_t Speed[4] = {0,30,60,100};
uint8_t Speed_MANUAL_index = 0;
uint8_t Speed_AUTO_index = 0;
uint8_t Status = 0;
float Temp;

/***************** 函数声明 ****************/
static void Sys_Init(void);
static void Sys_Get_Temp(void);
static void Sys_protect(void);
static void Sys_Mode_Change(void);
static void Sys_ShowData(void);

/****************** 主程序 *****************/
int main()
{
	// 系统初始化
	Sys_Init();

	while(1)
	{
		// 获取环境温度
		Sys_Get_Temp();
		// 保护模式
		Sys_protect();
		// 模式选择
		Sys_Mode_Change();
		// 数据显示
		Sys_ShowData();
	}
}

/*********************** 函数定义 **********************/
/* 系统初始化 */
static void Sys_Init(void)
{
	// 外设初始化
	OLED_Init();
	Key_Init();
	Motor_Init();
	AD_Init();
	IR_Init();
	LED_Init();
	
	// OLED显示
	OLED_ShowString(1,1,"Mode :");
	OLED_ShowString(2,1,"Temp :");
	OLED_ShowString(3,1,"Speed:");
	OLED_ShowString(4,1,"State:");
	
}
/* 温度获取 */
static void Sys_Get_Temp(void)
{
	Temp = AD_GetTemp();
}
/* 保护模式 */
static void Sys_protect(void)
{
	if(Project_Flag)
	{
		Project_Flag = 0;
		Delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 1)
		{
			
			OLED_ShowString(4,7,"PROTECT");
			Motor_SetSpeed(0);
			OLED_ShowNum(3,7,0,3);
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 1);
		}
	}
}
/* 模式选择 */
static void Sys_Mode_Change(void)
{
	if(Key1_Flag)
	{
		Key1_Flag = 0;
		Delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
		{
			Status = ~Status;
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
		}
	}
	if(Status == 0)
	{
		Speed_MANUAL_index = 0;
		if(Temp<25)
		{
			Speed_AUTO_index = 1;
		}
		else if(Temp>=25 && Temp<=30)
		{
			Speed_AUTO_index = 2;
		}
		else
		{
			Speed_AUTO_index = 3;
		}
		LED1_Mode_AUTO();
		LED2_Speed(Speed_AUTO_index);
		OLED_ShowString(1,7,"AUTO  ");
		Motor_SetSpeed(Speed[Speed_AUTO_index]);
		OLED_ShowNum(3,7,Speed[Speed_AUTO_index],3);
	}
	else
	{
		if(Key2_Flag)
		{
			Key2_Flag = 0;
			Delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
			{
				Speed_MANUAL_index++;
				Speed_MANUAL_index%=4;
				while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
			}
			
		}
		LED1_Mode_MANUAL();
		LED2_Speed(Speed_MANUAL_index);
		OLED_ShowString(1,7,"MANUAL");
		Motor_SetSpeed(Speed[Speed_MANUAL_index]);
		OLED_ShowNum(3,7,Speed[Speed_MANUAL_index],3);
	}
}
/* 数据显示 */
static void Sys_ShowData(void)
{
	OLED_ShowNum(2,7,Temp,2);
	OLED_ShowChar(2,9,'.');
	OLED_ShowNum(2,10,(uint16_t)(Temp*10)%10,1);
	OLED_ShowString(4,7,"SAFE   ");
}
