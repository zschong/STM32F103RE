#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#include "spi.h"
#include "systick.h"


#define DELAY	DelayMSecond(100)

void LedInit(void)
{
	GpioInit(PA6, GPIO_Mode_AF_PP, GPIO_Speed_50MHz); //AO-LED
	GpioInit(PA7, GPIO_Mode_AF_PP, GPIO_Speed_50MHz); //AO-LED
	GpioInit(PB0, GPIO_Mode_AF_PP, GPIO_Speed_50MHz); //AO-LED
	GpioInit(PB1, GPIO_Mode_AF_PP, GPIO_Speed_50MHz); //AO-LED
	
	GpioInit(PC0, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AO-LED-COLOR
	GpioInit(PC1, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AO-LED-COLOR
	GpioInit(PC2, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AO-LED-COLOR
	GpioInit(PC3, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //AO-LED-COLOR
	
	GpioInit(PC7, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //DO-LED
	GpioInit(PD2, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); //ÔËÐÐ-LED
}
void UsartInit(void)
{
	GpioInit(PA9, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//TX
	GpioInit(PA10, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);	//RX
	GpioInit(PA11, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//RW
	UsartConfig(USART1, 9600, 0, 8, 1);
		
	GpioInit(PA2, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//TX
	GpioInit(PA3, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);	//RX
	GpioInit(PA1, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//RW
	UsartConfig(USART2, 9600, 0, 8, 1);
	
//	UsartConfig(USART3, 115200, 0, 8, 1);
//	UsartConfig(UART4, 115200, 0, 8, 1);
//	UsartConfig(UART5, 115200, 0, 8, 1);
}

void PwmInit(void)
{
	PwmConfig(TIM3, 100, 719, 0, 1);
	PwmConfig(TIM3, 100, 719, 0, 2);
	PwmConfig(TIM3, 100, 719, 0, 3);
	PwmConfig(TIM3, 100, 719, 0, 4);	
}

void SpiInit(void)
{
	GpioInit(PA12, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//NSS
	GpioInit(PA13, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//SCK
	GpioInit(PA14, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//MISO
	GpioInit(PA15, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	//MOSI
	SPI1Config();
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

int main(void)
{
	uint32_t timeout = 0;
	uint32_t timeout1 = 0;
	uint32_t timeout2 = 0;
	uint32_t timeout3 = 0;
	uint32_t timeout4 = 0;
	uint32_t timeout5 = 0;
	
	LedInit();
	PwmInit();
	SpiInit();
	SystickInit();
	UsartInit();

	while(1)
	{
		if( Timeout(&timeout, 200) )
		{
			static int i = 0; i++;
			
			if( Timeout(&timeout5, 1000) )
			{
				i%2 ? GpioOn(PD2) : GpioOff(PD2);
			}
			TuneLight(1, i%2, i%100, &timeout1);
			TuneLight(2, i%2, i%100, &timeout2);
			TuneLight(3, i%2, i%100, &timeout3);
			TuneLight(4, i%2, i%100, &timeout4);
			
			i%2 ? GpioOn(PC7) : GpioOff(PC7);
			
			GpioOn(PA11);
			printf("PA11.On: sysclock=%d\n", SystemCoreClock);
			DelayMSecond(10);
			GpioOff(PA11);
			
			GpioOn(PA1);
			UsartSend(USART2, "USART2 is ok\n", 13);
			DelayMSecond(10);
			GpioOff(PA1);
		}
	}
}
