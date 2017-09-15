# STM32F103RE
STM32F103RE

```c
#include <string.h>
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#include "ai.h"
#include "ao.h"
#include "rtc.h"
#include "eeprom.h"
#include "systick.h"
#include "stdiox.h"


#define DELAY	DelayMSecond(100)

void LedInit(void)
{
	GpioInit(PC7, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //DO-LED
	GpioInit(PD2, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //运行-LED
}
void UsartInit(void)
{
	GpioInit(PA11, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);			//RW
	GpioInit(PA9, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);			//TX
	GpioInit(PA10, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);	//RX
	UsartConfig(USART1, 9600, 0, 8, 1);
		
	GpioInit(PA1, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);			//RW
	GpioInit(PA2, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);			//TX
	GpioInit(PA3, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);		//RX
	UsartConfig(USART2, 9600, 0, 8, 1);

	GpioOn(PA1);
}

void PwmInit(void)
{
	PwmConfig(TIM3, 100, 719, 0, 1);
	PwmConfig(TIM3, 100, 719, 0, 2);
	PwmConfig(TIM3, 100, 719, 0, 3);
	PwmConfig(TIM3, 100, 719, 0, 4);	
}


void TuneLight(int channel, int color, int level, uint32_t *timeout)
{
	if( Timeout(timeout, 500) )
	{
		if( color )
		{
			GpioPinOn(GPIOC, channel-1);
		}
		else
		{
			GpioPinOff(GPIOC, channel-1);
		}
		PwmConfig(TIM3, 100, 710, (level/10)*10, channel);
	}
}
void SystickInit(void)
{
	SystickConfig();
}
void AiInit(void)
{
	AiConfig();
}
void AoInit(void)
{
	GpioInit(PA6, GPIO_Mode_AF_PP, GPIO_Speed_50MHz); //AO-LED
	GpioInit(PA7, GPIO_Mode_AF_PP, GPIO_Speed_50MHz); //AO-LED
	GpioInit(PB0, GPIO_Mode_AF_PP, GPIO_Speed_50MHz); //AO-LED
	GpioInit(PB1, GPIO_Mode_AF_PP, GPIO_Speed_50MHz); //AO-LED
	
	GpioInit(PC0, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AO-LED-COLOR
	GpioInit(PC1, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AO-LED-COLOR
	GpioInit(PC2, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AO-LED-COLOR
	GpioInit(PC3, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AO-LED-COLOR
	
	AoConfig();
}
void RtcInit(void)
{
	RtcConfig();
}
void EepromInit(void)
{
	EepromConfig();
}

/*----------- test ----------*/
void LedTest(void)
{
	static int i = 0;
	static uint32_t timeout1 = 0;
	static uint32_t timeout2 = 0;
	static uint32_t timeout3 = 0;
	static uint32_t timeout4 = 0;
	static uint32_t timeout5 = 0;

	TuneLight(1, i%2, i%100, &timeout1);
	TuneLight(2, i%2, i%100, &timeout2);
	TuneLight(3, i%2, i%100, &timeout3);
	TuneLight(4, i%2, i%100, &timeout4);

	if( Timeout(&timeout5, 1000) )
	{
		GpioOff(PD2);
		GpioOff(PC7);
	}
	else
	{
		GpioOn(PD2);
		GpioOn(PC7);
	}
	i += 11;
}
void AiTest(void)
{
	for(int i = 0; i < 8; i++)
	{
		printf("AI[%d] = %f", i, AiGetValue(i));
		DelayMSecond(10);
		printf("\n");
	}
}
void AoTest(void)
{
	for(int i = 0; i < 1; i++)
	{
		AoReset(i);
		DelayMSecond(10);

		AoSetType(i, AO_Type_0_To_10_V);
		DelayMSecond(10);

		AoSetValue(i, 3.0);
		DelayMSecond(10);

		printf("AO[%d].Status =%04X ", i, AoGetStatus(i));
		DelayMSecond(10);
		printf("\n");

		printf("AO[%d].Control =%04X ", i, AoGetControl(i));
		DelayMSecond(10);
		printf("\n");

		printf("AO[%d].Value =%f ", i, AoGetValue(i));
		DelayMSecond(10);
		printf("\n");
		DelayMSecond(10);
		printf("\n");
	}
}
void RtcTest(void)
{
	RtcType_t time;

	RtcGet(&time);
}
void EepromTest(void)
{
	uint8_t rbuf1[0x100] = {0};
	uint8_t rbuf2[0x100] = {0};
	uint8_t wbuf1[0x100] = {0};
	uint8_t wbuf2[0x100] = {0};

	for(uint32_t i = 0; i < sizeof(wbuf1); i++)
	{
		rbuf1[i] = (uint8_t)0;
		rbuf2[i] = (uint8_t)0;
		wbuf1[i] = (uint8_t)(i+0xAA);
		wbuf2[i] = (uint8_t)(i+0x11);
	}
	EepromWrite(0, wbuf1, sizeof(wbuf1));
	DelayMSecond(1);
	EepromRead(0, rbuf1, sizeof(rbuf1));
	DelayMSecond(1);
	EepromWrite((128 << 10) + 0, wbuf2, sizeof(wbuf2));
	DelayMSecond(1);
	EepromRead((128 << 10) + 0, rbuf2, sizeof(rbuf2));
	DelayMSecond(1);
}
void UsartTest(void)
{
	char *p = "USART2 is ok\n";
	GpioOn(PA1);
	UsartSend(USART2, p, strlen(p));
	DelayMSecond(10);
	GpioOff(PA1);
}
/*------------end of test -----------*/

int main(void)
{
	uint32_t timeout = 0;

	SystickInit();
	UsartInit();
	PwmInit();
	LedInit();
	AiInit();
	AoInit();
	RtcInit();
	EepromInit();

	while(1)
	{
		if( Timeout(&timeout, 200) )
		{	
			LedTest();
			AiTest();
			AoTest();
			RtcTest();
			EepromTest();
			UsartTest();
		}
	}
}

```
