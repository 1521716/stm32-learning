#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

void W25Q64_Init(void)
{
	MySPI_Init();
}


void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

void W25Q64_WaitBusy(void)
{
	uint32_t Timeout = 10000;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE)&0x01) == 0x01)
	{
		Timeout--;
		if(Timeout<=0)	break;
	}
	MySPI_Stop();
}

void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	uint16_t i;
	W25Q64_WriteEnable();
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(Address>>16);
	MySPI_SwapByte(Address>>8);
	MySPI_SwapByte(Address);
	for (i = 0; i < Count; i ++)				
	{
		MySPI_SwapByte(DataArray[i]);			
	}
	MySPI_Stop();	
	
	W25Q64_WaitBusy();
}

void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();						
	
	MySPI_Start();								
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);	
	MySPI_SwapByte(Address >> 16);				
	MySPI_SwapByte(Address >> 8);				
	MySPI_SwapByte(Address);					
	MySPI_Stop();								
	
	W25Q64_WaitBusy();							
}

/**
  * @brief  读取W25Q64厂商ID和设备ID（验证SPI通信是否正常）
  * @param  MID：输出参数，8位厂商ID（Winbond = 0xEF）
  * @param  DID：输出参数，16位设备ID（W25Q64 = 0x4017）
  * @retval 无
  */
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);		// 发送JEDEC ID命令 0x9F
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);	// 厂商ID
	*DID  = MySPI_SwapByte(W25Q64_DUMMY_BYTE) << 8;	// 设备ID高字节
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);		// 设备ID低字节
	MySPI_Stop();
}

void W25Q64_ReceiveData(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	uint16_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address >> 16);				
	MySPI_SwapByte(Address >> 8);				
	MySPI_SwapByte(Address);	
	for(i = 0;i<Count;i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	
	MySPI_Stop();
}
