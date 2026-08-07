#ifndef __ADC_H__
#define __ADC_H__

extern int16_t AD_Value[3];
void AD_Init(void);
void AD_GetCount(float *T,uint8_t *Light,float *Dist_V);

#endif
