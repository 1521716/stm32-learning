#ifndef __LED_H__
#define __LED_H__

#define LED1 GPIO_Pin_0
#define LED2 GPIO_Pin_1
#define LED3 GPIO_Pin_2
#define LED4 GPIO_Pin_3

void LED_Init(void);
void LED_SetState(uint16_t LEDNum,uint8_t BitValue);
void LED_SetStatus(uint8_t ByteValue);

#endif
