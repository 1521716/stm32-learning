#include "stm32f10x.h"                  // Device header

/**
  * @brief  控制SS状态
  * @param  BitValue 高低电平
  * @retval  无
  */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
}

/**
  * @brief  控制SCL状态
  * @param  BitValue 高低电平
  * @retval  无
  */
void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)BitValue);
}

/**
  * @brief  向MOSI移入一个比特
  * @param  BitValue 0=0，1=1
  * @retval  无
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)BitValue);
}

/**
  * @brief  读取一个比特
  * @param  无
  * @retval  读取的数据
  */
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}

/**
  * @brief  SPI软件初始化
  * @param  无
  * @retval  无
  */
void MySPI_Init(void)
{
	// RCC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	// GPIO配置
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	MySPI_W_SS(1);// 初始为高电平，拉低开始通信
	MySPI_W_SCK(0);// 模式0
}

/**
  * @brief  SPI开始
  * @param  无
  * @retval  无
  */
void MySPI_Start(void)
{
	MySPI_W_SS(0);
}

/**
  * @brief  SPI结束
  * @param  无
  * @retval  无
  */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}

/**
  * @brief  交换一个字节数据
  * @param  ByteSend 主机发送的数据
  * @retval  主机接收的数据
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t ByteReceive = 0x00;
	uint8_t i;
	
	for(i = 0;i<8;i++)
	{
		MySPI_W_MOSI(ByteSend & (0x80>>i));
		MySPI_W_SCK(1);
		if(MySPI_R_MISO() == 1)	{ByteReceive |= (0x80>>i);}
		MySPI_W_SCK(0);
	}
	return ByteReceive;
}
