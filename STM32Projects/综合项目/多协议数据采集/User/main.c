#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <string.h>
#include "Key.h"
#include "OLED.h"
#include "Delay.h"
#include "ADC.h"
#include "W25Q64.h"
#include "MPU6050.h"
#include "USART.h"

#define MAXSIZE 51
#define DATA_BASEADDRESS 0x000000

uint8_t record_index = 0;
uint8_t record_count = 0;

float T,Dist_V;
uint8_t Light;
int16_t AX, AY, AZ, GX, GY, GZ;

uint8_t Status = 0;


int main()
{
	OLED_Init();
	AD_Init();
	Key_Init();
	W25Q64_Init();
	MPU6050_Init();
	MyUSART_Init();
	
	while(1)
	{
		AD_GetCount(&T,&Light,&Dist_V);
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);	
		
		if(cmd_Flag == 1)
		{
			cmd_Flag = 0;
			if(strcmp(receive_buf,"QUERY") == 0)
			{
				printf("Temp:");
			}
		}
		if(Key1_Flag == 1)
		{
			Key1_Flag = 0;
			OLED_Clear();
			Status = ~Status;
		}
		if(Status == 0)
		{
			OLED_ShowString(1,1,"Temp :   C");
			OLED_ShowString(2,1,"Light:   %");
			OLED_ShowString(3,1,"DistV:   V");
			
			OLED_ShowNum(1,7,T,3);
			OLED_ShowNum(2,7,Light,3);
			OLED_ShowNum(3,7,Dist_V,3);
			
			
			if(Key2_Flag == 1)
			{
				Key2_Flag = 0;
				if(record_count>=50)
				{
					record_count = 0;
					record_index = 0;
					W25Q64_SectorErase(DATA_BASEADDRESS);
				}
				uint8_t Temp[5];
				uint16_t t = T*10,v = Dist_V * 100;
				Temp[0] = t>>8;Temp[1] = t&0xFF;Temp[2] = Light;Temp[3] = v>>8;Temp[4] = v&0xFF;
				W25Q64_PageProgram(DATA_BASEADDRESS+record_index*sizeof(Temp),Temp,5);
				record_count++;
				record_index = (record_index+1)%MAXSIZE;
			
			}
		}
		else
		{	
			OLED_ShowString(1,1,"Acc:   Gyro:");
			OLED_ShowSignedNum(2, 1, AX, 5);					
			OLED_ShowSignedNum(3, 1, AY, 5);
			OLED_ShowSignedNum(4, 1, AZ, 5);
			OLED_ShowSignedNum(2, 8, GX, 5);
			OLED_ShowSignedNum(3, 8, GY, 5);
			OLED_ShowSignedNum(4, 8, GZ, 5);
		}
	}
}
