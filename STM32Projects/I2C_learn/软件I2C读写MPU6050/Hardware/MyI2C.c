#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  * @brief  拉低或者释放SCL
  * @param  BitValue 拉低或释放
  * @retval  无
  */
void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}

/**
  * @brief  拉低或者释放SDA
  * @param  BitValue 拉低或释放
  * @retval  无
  */
void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}

/**
  * @brief  读取SDA电平
  * @param  无
  * @retval  SDA此时电平
  */
uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}

/**
  * @brief  I2C软件初始化，配置SDA和SCL为开漏输出，并释放
  * @param  无
  * @retval  无
  */
void MyI2C_Init(void)
{
	// 将SDA和SCL引脚配置为开漏输出，并置为高电平
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_11 | GPIO_Pin_10);
}

/**
  * @brief  开始
  * @param  无
  * @retval  无
  */
void MyI2C_Start(void)
{
	// 起始先释放SDA和SCL
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	
	// 拉低SDA
	MyI2C_W_SDA(0);
	
	// 拉低SCL（与后续操作拼接）
	MyI2C_W_SCL(0);
}

/**
  * @brief  结束
  * @param  无
  * @retval  无
  */
void MyI2C_Stop(void)
{
	// 先拉底SDA
	MyI2C_W_SDA(0);
	
	// 释放SCL
	MyI2C_W_SCL(1);
	
	// 释放SDA
	MyI2C_W_SDA(1);
}

/**
  * @brief  发送一个字节数据
  * @param  Byte 要发送的字节数据
  * @retval  无
  */
void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i = 0;i<8;i++)
	{
		MyI2C_W_SDA(Byte & (0x80>>i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}

/**
  * @brief  接收一个字节数据
  * @param  无
  * @retval  要接收的字节数据
  */
uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t Byte = 0x00,i;
	MyI2C_W_SDA(1);
	for(i = 0;i<8;i++)
	{
		MyI2C_W_SCL(1);
		if(MyI2C_R_SDA() == 1)	{Byte |= (0x80>>i);}
		MyI2C_W_SCL(0);
	}
	return Byte;
}

/**
  * @brief  发送应答位
  * @param  AckBit 0=主机成功接收，1=主机未成功接收
  * @retval  无
  */
void MyI2C_SendAck(uint8_t AckBit)
{
	
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);

}

/**
  * @brief  接收应答位
  * @param  无
  * @retval  0=从机成功接收，1=从机未成功接收
  */
uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	
	MyI2C_W_SDA(1);
	
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);

	return AckBit;
}
