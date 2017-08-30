#include "spi.h"


void SPI1Config(void)
{
	SPI_InitTypeDef SPI_InitStructure;

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode		= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL		= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA		= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS		= SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit			= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial		= 7;

	SPI_Init(SPI1, &SPI_InitStructure);
}

void SPI1SendWord(uint16_t word)
{
	int timeout = 0x1000;
	while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET )
	{
		if( timeout-- < 1 )
		{
			return;
		}
	}
	SPI_I2S_SendData(SPI1, word);
}

uint16_t SPI1ReadWord(void)
{
	int timeout = 0x1000;
	while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET )
	{
		if( timeout-- < 1 )
		{
			return (uint16_t)-1;
		}
	}
	return SPI_I2S_ReceiveData(SPI1);
}
