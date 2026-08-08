#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"

uint8_t Num = 0;

int main()
{
	LED_Init();
	
	while(1)
	{
		Num++;
		/*LED_SetStatus(~Num);*/
		LED_SetState(LED1,~(Num & 0x01));
		LED_SetState(LED2,~(Num & 0x02));
		LED_SetState(LED3,~(Num & 0x04));
		LED_SetState(LED4,~(Num & 0x08));
		Delay_ms(500);
	}
}
