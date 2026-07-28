#ifndef __IC_H__
#define __IC_H__

extern uint8_t TIM4_Flag;

void IC_Init(void);
uint32_t IC_GetFreq(void);

#endif
