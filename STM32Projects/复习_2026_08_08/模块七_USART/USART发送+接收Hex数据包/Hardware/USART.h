#ifndef __USART_H__
#define __USART_H__
#include <stdio.h>

extern uint8_t TxPacket[];
extern uint8_t RxPacket[];

void MyUSART_Init(void);
void MyUSART_SendByte(uint8_t Byte);
void MyUSART_SendArray(uint8_t *Array,uint16_t Length);
void MyUSART_SendString(char *String,uint16_t Length);
void MyUSART_SendPacket(void);
uint8_t MyUSART_GetRxFlag(void);
uint8_t MyUSART_GetRxData(void);

#endif
