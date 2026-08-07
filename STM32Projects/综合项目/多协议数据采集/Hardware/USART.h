#ifndef __USART_H__
#define __USART_H__

extern char receive_buf[30];
extern uint8_t receive_index;
extern uint8_t cmd_Flag;

void MyUSART_Init(void);
void MyUSART_SendByte(uint8_t Byte);
void MyUSART_SendArray(uint8_t *Array,uint16_t Count);
void MyUSART_SendString(char* String);


#endif
