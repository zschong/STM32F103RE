#include "ai.h"
#include "gpio.h"

void AiConfig(void)
{
	GpioInit(PB12, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//SPI2-NSS
	GpioInit(PB13, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-SCLK
	GpioInit(PB14, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-MISO
	GpioInit(PB15, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-MOSI
	GpioInit(PC13, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//Ai-CHIP-SELECT
	SpiConfig(SPI2);
}
void AiChipSelect(void)
{
	GpioOff(PC13);
	GpioOff(PB12);
}
void AiChipUnselect(void)
{
	GpioOn(PB12);
	for(int i = 0; i < 16; i++);
	GpioOff(PB12);
	GpioOn(PC13);
}
float AiGetValue(int i)
{
	uint32_t x = i % 8;
	uint16_t CFG = (1 << 13 | 7 << 10 | x << 7 | 1 << 6 | 1 << 3 | 1);

	AiChipSelect();
	SpiSendWord(SPI2, CFG << 2);
	AiChipUnselect();

	return (4.096 / (1 << 16) * 5.0 / 2.0 * SpiReadWord(SPI2));
}
