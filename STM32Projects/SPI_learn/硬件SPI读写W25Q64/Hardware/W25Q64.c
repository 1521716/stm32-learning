#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

/**
  * @brief  W25Q64初始化
  * @param  无
  * @retval  无
  */
void W25Q64_Init(void)
{
	MySPI_Init();
}

/**
  * @brief  获取W25Q64的厂商ID和设备ID
  * @param  *MID 厂商ID地址，*DID 设备ID地址
  * @retval  无
  */
void W25Q64_ReadID(uint8_t *MID,uint16_t *DID)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID<<=8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	MySPI_Stop();
}

/**
  * @brief  写使能
  * @param  无
  * @retval  无
  */
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

/**
  * @brief  等待忙事件结束（有时限）
  * @param  无
  * @retval  无
  */
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	Timeout = 100000;
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01)==1)
	{
		Timeout--;
		if(Timeout == 0)
			break;
	}
	MySPI_Stop();
}

/**
  * @brief  页编程
  * @param  Address 页地址
  * @param  DataArray 写入数据的数组地址
  * @param  Count 写入数据的数量
  * @retval  无
  */
void W25Q64_PageProgram(uint32_t Address,uint8_t *DataArray,uint16_t Count)
{
	W25Q64_WriteEnable();
	
	uint16_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(Address>>16);
	MySPI_SwapByte(Address>>8);
	MySPI_SwapByte(Address);
	for(i = 0;i<Count;i++)
	{
		MySPI_SwapByte(DataArray[i]);
	}
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

/**
  * @brief  擦除页
  * @param  Address 要擦除的页地址
  * @retval  无
  */
void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(Address>>16);
	MySPI_SwapByte(Address>>8);
	MySPI_SwapByte(Address);
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

/**
  * @brief  读取数据
  * @param  Address 读取数据的地址
  * @param  DataArray 将读取数据的存入的地址
  * @param  Count 读取数据的数量
  * @retval  无
  */
void W25Q64_ReadData(uint32_t Address,uint8_t *DataArray,uint32_t Count)
{
	uint32_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address>>16);
	MySPI_SwapByte(Address>>8);
	MySPI_SwapByte(Address);
	for(i = 0;i<Count;i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
}
