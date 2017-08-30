#include "systick.h"

static uint32_t tickcount = 0;

uint32_t SystickConfig(void)
{
	return SysTick_Config(SystemCoreClock/1000);
}
uint32_t GetTimeMSecond(void)
{
	return tickcount;
}
uint32_t GetTimeSecond(void)
{
	return tickcount/1000;
}
uint32_t Timeout(uint32_t *last, uint32_t timeout)
{
	if( 0 == last )
	{
		return 0;
	}
	if( tickcount - *last < timeout )
	{
		return 0;
	}
	*last = tickcount;
	return 1;
}
void DelayMSecond(uint32_t ms)
{
	uint32_t last = tickcount;
	while(tickcount - last < ms);
}
void SysTick_Handler(void)
{
	tickcount++;
}
