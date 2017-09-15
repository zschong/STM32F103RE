#include "ai.h"
#include "gpio.h"
#include "stdiox.h"

void AiConfig(void)
{
	GpioInit(PB12, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//SPI2-NSS
	GpioInit(PB13, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-SCLK
	GpioInit(PB14, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-MISO
	GpioInit(PB15, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SPI2-MOSI
	GpioInit(PC13, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//Ai-CHIP-SELECT
	SpiConfig(SPI2);
	GpioOn(PB12);
	GpioOn(PC13);
}
void AiChipSelect(void)
{
	GpioOff(PC13);
//	GpioOn(PB12);
//	for(int i = 0; i < 60; i++);
	GpioOff(PB12);
}
void AiChipUnselect(void)
{
	GpioOn(PB12);
	for(int i = 0; i < 60; i++);
//	GpioOff(PB12);
	GpioOn(PC13);
}
float AiGetValue(int i)
{
	uint16_t v = 0;
	uint32_t x = 0;
	uint16_t CFG = 0;

	switch(i)
	{
		case 1:
		case 2:
		case 3:
		case 4:
			x = i-1;
			break;
		case 5:
			x = 7;
			break;
		case 6:
			x = 6;
			break;
		case 7:
			x = 5;
			break;
		case 8:
			x = 4;
			break;
	}
	
	CFG = (1 << 13 | 7 << 10 | x << 7 | 1 << 6 | 1 << 3 | 1);
	
	AiChipSelect();
	SpiSendWord(SPI2, CFG << 2);
	v = SpiReadWord(SPI2);
	AiChipUnselect();

	AiChipSelect();
	SpiSendWord(SPI2, CFG << 2);
	v = SpiReadWord(SPI2);
	AiChipUnselect();

	
	printf("AiGetValue(x=%d, v=%04X\n ", x, v);

	return (4.096 * 5.0 / 2.0 * v / 65535.0) * 2;
}
