#include "gpio.h"
#include "stdiox.h"
#include "AD5412.h"

void AD5412_Config(void)
{
	GpioInit(PB12, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//SPI2-NSS
	GpioInit(PB13, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-SCLK
	GpioInit(PB14, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-MISO
	GpioInit(PB15, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-MOSI
	GpioInit(PC14, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//AD5412_1-CHIP-SELECT
	GpioInit(PC15, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//AD5412_2-CHIP-SELECT
	SpiConfig(SPI2);
	for(int i = 0; i < AD5412_MAX; i++)
	{
		AD5412_Reset(i);
		AD5412_SetType(i, AD5412_Type_0_To_10_V);
	}
}
void AD5412_ChipSelect(int i)
{
	switch(i)
	{
		case 1:
			GpioOff(PC14);
			break;
		case 2:
			GpioOff(PC15);
			break;
	}
	GpioOff(PB12);
}
void AD5412_ChipUnselect(int i)
{
	GpioOn(PB12);
	for(int i = 0; i < 20; i++);
	GpioOff(PB12);

	GpioOn(PC14);
	GpioOn(PC15);
}

void AD5412_Write(int i, uint32_t value)
{
	AD5412_ChipSelect(i);
	SpiSendByte(SPI2, value >> 16);
	SpiSendWord(SPI2, value >>  0);
	AD5412_ChipUnselect(i);
}

uint16_t AD5412_Read(int i)
{
	uint16_t a = 0;
	uint16_t b = 0;

	AD5412_ChipSelect(i);
	SpiSendByte(SPI2, 0);
	a = SpiReadWord(SPI2);
	SpiSendWord(SPI2, 0);
	b = SpiReadWord(SPI2);
	AD5412_ChipUnselect(i);

	printf("AD5412_Read: a = %04X, b = %04X \n ", a, b);

	return SpiReadWord(SPI2);
}

void AD5412_Reset(int i)
{
	AD5412_Write(i, AD5412_Cmd_Reset << 16 | 1);
}
void AD5412_SetType(int i, AD5412_Type_t type)
{
	AD5412_Write(i, AD5412_Cmd_Control << 16 | 1 << 12 | type);
}

void AD5412_SetValue(int i, uint16_t value)
{
	AD5412_Write(i, AD5412_Cmd_Set << 16 | (0xffff & (value - 1) << 4));
}

uint16_t AD5412_GetStatus(int i)
{
	AD5412_Write(i, AD5412_Cmd_Get << 16 | AD5412_Get_Status);
	return AD5412_Read(i);
}

uint16_t AD5412_GetControl(int i)
{
	AD5412_Write(i, AD5412_Cmd_Get << 16 | AD5412_Get_Control);
	return AD5412_Read(i);
}

uint16_t AD5412_GetValue(int i)
{
	AD5412_Write(i, AD5412_Cmd_Get << 16 | AD5412_Get_Value);
	for(int i = 0; i < 16; i++);
	return (AD5412_Read(i) >> 4);
}
