#ifndef __MOTOR_H__
#define __MOTOR_H__

void Motor_Init(void);
int16_t Encoder_GetCount(void);
int8_t Motor_GetSpeed(void);
void Motor_SetSpeed(int8_t Speed);

#endif
