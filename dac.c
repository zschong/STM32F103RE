#include "dac.h"
#include "gpio.h"

void DacConfig(void)
{
	DAC_InitTypeDef DAC_InitStructur;

	GpioInit(PA4, GPIO_Mode_AIN, GPIO_Speed_10MHz);
	GpioInit(PA5, GPIO_Mode_AIN, GPIO_Speed_10MHz);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
	DAC_InitStructur.DAC_Trigger		= DAC_Trigger_None;
	DAC_InitStructur.DAC_OutputBuffer	= DAC_OutputBuffer_Disable;
	DAC_InitStructur.DAC_WaveGeneration = DAC_WaveGeneration_None;

	DAC_Init(DAC_Channel_1, &DAC_InitStructur);
	DAC_Init(DAC_Channel_2, &DAC_InitStructur);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_Cmd(DAC_Channel_2, ENABLE);
	DAC->CR = 0x00030003;
}
uint16_t DacGetValue(int i)
{
	switch(i)
	{
		case 1:
			return DAC->DOR1;
		case 2:
			return DAC->DOR2;
	}
	return DAC->DOR1;
}
void DacSetValue(int i, uint16_t value)
{
	switch(i)
	{
		case 1:
			DAC_SetChannel1Data(DAC_Align_12b_R, value);
			break;
		case 2:
			DAC_SetChannel2Data(DAC_Align_12b_R, value);
			break;
	}
}
