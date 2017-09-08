#include "ao.h"
#include "gpio.h"

void AoConfig(void)
{
	GpioInit(PB12, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//SPI2-NSS
	GpioInit(PB13, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-SCLK
	GpioInit(PB14, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-MISO
	GpioInit(PB15, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-MOSI
	GpioInit(PC14, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//Ao1-CHIP-SELECT
	GpioInit(PC15, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//Ao2-CHIP-SELECT
	SpiConfig(SPI2);
	for(int i = 0; i < AO_MAX; i++)
	{
		AoReset(i);
		AoSetType(i, AO_Type_0_To_10_V);
		AoSetValue(i, 2.3000);
	}
}
void AoChipSelect(int i)
{
	switch(i)
	{
		case 0:
			GpioOff(PC14);
			break;
		case 1:
			GpioOff(PC15);
			break;
	}
	GpioOff(PB12);
}
void AoChipUnselect(int i)
{
	GpioOn(PB12);
	for(int i = 0; i < 20; i++);
	GpioOff(PB12);

	switch(i)
	{
		case 0:
			GpioOn(PC14);
			break;
		case 1:
			GpioOn(PC15);
			break;
	}
}
uint16_t AoWrite(int i, uint32_t value)
{
	uint8_t cmd  = (uint8_t)(value >> 16);
	uint16_t data = (uint16_t)(value >> 00);

	AoChipSelect(i);
	SpiSendByte(SPI2, cmd);
	SpiSendWord(SPI2, data);
	while( SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET );
	AoChipUnselect(i);

	return SpiReadWord(SPI2);
}
uint16_t AoReset(int i)
{
	return AoWrite(i, AO_Cmd_Reset << 16 | 1);
}
uint16_t AoGetStatus(int i)
{
	return AoWrite(i, AO_Cmd_Get << 16 | AO_Get_Status);
}
float AoGetValue(int i)
{
	float value = 0.0;
	uint16_t data = 0;
	
	data = AoWrite(i, AO_Cmd_Get << 16 | AO_Get_Value);
	value = data;

	return value;
}
uint16_t AoGetControl(int i)
{
	return AoWrite(i, AO_Cmd_Control << 16 | AO_Get_Control);
}
uint16_t AoSetType(int i, AOType_t type)
{
	return AoWrite(i, AO_Cmd_Set << 16 | 1 << 12 | type);
}
void AoSetValue(int i, float value)
{
	uint16_t data = value / 10.0 * 4096;

	AoWrite(i, AO_Cmd_Set << 16 | data << 4);
}
