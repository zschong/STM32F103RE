#include "di.h"

/*----------------- private ----------------*/
bool DiGet(int gpio)
{
	return GPIO_ReadInputDataBit(GetPort(gpio), 0xffff & gpio);
}

/*----------------- public ----------------*/
void DiConfig(void)
{
	GpioInit(PC10, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(PC11, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(PC12, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(PA15, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
}
bool DiGetValue(int i)
{
	switch(i)
	{
		case 1:
			return DiGet(PC12);
		case 2:
			return DiGet(PC11);
		case 3:
			return DiGet(PC10);
		case 4:
			return DiGet(PA15);
	}
	return false;
}
