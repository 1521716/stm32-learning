#ifndef __PWM_H__
#define __PWM_H__

void PWM_Init(void);
void PWM_SetPrescaler(uint16_t Prescaler);
void PWM_SetDuty(uint8_t Duty);

#endif
