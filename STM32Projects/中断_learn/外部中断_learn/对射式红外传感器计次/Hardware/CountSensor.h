#ifndef __COUNT_SENSOR_H__
#define __COUNT_SENSOR_H__

extern uint16_t CountSensor_Count;
extern uint8_t CountSensor_Flag;

void CountSensor_Init(void);
uint16_t CountSensor_Get(void);
uint8_t CountSensor_GetFlag(void);

#endif
