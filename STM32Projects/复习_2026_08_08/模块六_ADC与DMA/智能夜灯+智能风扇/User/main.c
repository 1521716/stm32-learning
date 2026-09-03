#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "PWM.h"
#include "Motor.h"

uint16_t Light,Temp;

int main()
{
	OLED_Init();
	AD_Init();
	PWM_Init();
	Motor_Init();
	
	OLED_ShowString(1,1,"Light:");
	OLED_ShowString(2,1,"Temp :");
	
	while(1)
	{
		Light = ADValue[0];
		Temp = ADValue[1];
		/*  灯光控制  */
		if(Light<=2000 && Light>=1500)
		{
			PWM_SetDuty(60);
		}
		else if(Light<1500 && Light>=750)
		{
			PWM_SetDuty(30);
		}
		else if(Light<750)
		{
			PWM_SetDuty(0);
		}
		else if(Light>2000)
		{
			PWM_SetDuty(100);
		}
		/*  电机控制  */
		if(Temp<=2000 && Temp>=1500)
		{
			Motor_SetDuty(60);
		}
		else if(Temp<1500 && Temp>=750)
		{
			Motor_SetDuty(30);
		}
		else if(Temp<750)
		{
			Motor_SetDuty(0);
		}
		else if(Temp>2000)
		{
			Motor_SetDuty(100);
		}
		
		
		OLED_ShowNum(1,7,Light,4);
		OLED_ShowNum(2,7,Temp,4);
		
		Delay_ms(500);
	}
}
