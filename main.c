#include <string.h>
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#include "di.h"
#include "do.h"
#include "ai.h"
#include "ao.h"
#include "rtc.h"
#include "eeprom.h"
#include "systick.h"
#include "stdiox.h"
#include "AD5412.h"


#define DELAY	DelayMSecond(100)

void LedInit(void)
{
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
	if( Timeout(timeout, 200) )
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
void DiInit(void)
{
	DiConfig();
}
void DoInit(void)
{
	DoConfig();
}
void AiInit(void)
{
	//Gpio On(4~20mA), GpioOff(0~10V)
	GpioInit(PC5, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AI1-LED-COLOR
	GpioInit(PB9, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AI2-LED-COLOR
	GpioInit(PB5, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AI3-LED-COLOR
	GpioInit(PB8, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AI4-LED-COLOR
	GpioInit(PA12, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);//AI5-LED-COLOR
	GpioInit(PA8, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AI6-LED-COLOR
	GpioInit(PC9, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AI7-LED-COLOR
	GpioInit(PC8, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AI8-LED-COLOR
	AiConfig();
	GpioOff(PC5); 
	GpioOff(PB9);
	GpioOff(PB5);
	GpioOff(PB8);
	GpioOff(PA12);
	GpioOff(PA8);
	GpioOff(PC9);
	GpioOff(PC8); 

//	GpioOn(PC5); 
//	GpioOn(PB9);
//	GpioOn(PB5);
//	GpioOn(PB8);
//	GpioOn(PA12);
//	GpioOn(PA8);
//	GpioOn(PC9);
//	GpioOn(PC8); 
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
	}
	else
	{
		GpioOn(PD2);
	}
	i += 11;
}
void DiTest(void)
{
	for(int i = 1; i < MAX_DI+1; i++)
	{
		printf("DI[%d] = %d \n ", i, DiGetValue(i));
	}
}
void DoTest(void)
{
	static uint32_t timeout = 0;

	if( Timeout(&timeout, 1000) )
	{
		static bool value = false;

		for(int i = 1; i < MAX_DO+1; i++)
		{
			DoSetValue(i, value);
			printf("DO[%d] = %d\n ", i, DoGetValue(i));
		}
		value = !value;
	}
}
void AiTest(void)
{
	for(int i = 1; i < MAX_AI+1; i++)
	{
		printf("AI[%d] = %f \n ", i, AiGetValue(i));
		DelayMSecond(1);
	}
}
void AoTest(void)
{
	for(int i = 1; i < MAX_AO+1; i++)
	{
		static uint32_t set = 0;

		if( set++ < 8 )
		{
			AoSetType(i, Ao_Type_0_10_V);
			AoSetValue(i, 1.9);
		}
		printf("AO[%d].Value=%f\n ", i, AoGetValue(i));
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
	DelayMSecond(10);
	EepromRead(0, rbuf1, sizeof(rbuf1));
	DelayMSecond(10);
	EepromWrite((128 << 10) + 0, wbuf2, sizeof(wbuf2));
	DelayMSecond(10);
	EepromRead((128 << 10) + 0, rbuf2, sizeof(rbuf2));
	DelayMSecond(10);
	if( memcmp(rbuf1, wbuf1, sizeof(rbuf1)) == 0 )
	{
		printf(" eeprom1 ok\n ");
	}
	if( memcmp(rbuf2, wbuf2, sizeof(rbuf2)) == 0 )
	{
		printf(" eeprom2 ok\n ");
	}
}
void UsartTest(void)
{
	char *p = "USART2 is ok\n";
	GpioOn(PA1);
	UsartSend(USART2, p, strlen(p));
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
	DiInit();
	DoInit();
	AiInit();
	AoInit();
	RtcInit();
	EepromInit();

	while(1)
	{
		if( Timeout(&timeout, 1000) )
		{	
//			LedTest();
			DiTest();
			DoTest();
			AiTest();
			AoTest();
			RtcTest();
			EepromTest();
			UsartTest();
		}
	}
}
