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

				// ---- QUERY：查询传感器实时数据 ----
			if(strcmp(receive_buf,"QUERY") == 0)
			{
				printf("=== Now ===\r\n");
				printf("Temp: %.1f C\r\n", T);
				printf("Light: %d %%\r\n", Light);
				printf("DistV: %.2f V\r\n", Dist_V);
				printf("Acc: X=%d Y=%d Z=%d\r\n", AX, AY, AZ);
				printf("Gyro: X=%d Y=%d Z=%d\r\n", GX, GY, GZ);
			}

			// ---- READ：读取W25Q64中存储的历史数据 ----
			if(strcmp(receive_buf,"READ") == 0)
			{
				uint8_t i;
				uint8_t buf[5];
				uint16_t temp_raw, distv_raw;
				float temp_val, distv_val;

				printf("================================\r\n");

				for(i = 0; i < 50; i++)
				{
					// 从Flash读取第i条记录，每条5字节
					W25Q64_ReceiveData(DATA_BASEADDRESS + i * 5, buf, 5);

					// 全是0xFF表示未写过（Flash擦除后的默认值），跳过
					if(buf[0] == 0xFF && buf[1] == 0xFF && buf[2] == 0xFF
					   && buf[3] == 0xFF && buf[4] == 0xFF)
						continue;

					// 还原原始数据（与存储编码对应）
					temp_raw  = (buf[0] << 8) | buf[1];   // T * 10
					distv_raw = (buf[3] << 8) | buf[4];   // Dist_V * 100
					temp_val  = temp_raw / 10.0f;
					distv_val = distv_raw / 100.0f;

					printf("%2d  T:%.1fC  L:%d%%  V:%.2fV\r\n",
						   i + 1, temp_val, buf[2], distv_val);
				}

				printf("================================\r\n");
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
