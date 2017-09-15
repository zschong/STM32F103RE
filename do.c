#include "do.h"

/*----------------- private -----------------*/
bool DoGet(int i)
{
	return (bool)(GPIO_ReadInputDataBit(GetPort(i), 0xffff & i) != 0 );
}
void DoSet(int gpio, bool value)
{
	if( value )
	{
		GpioOn(gpio);
	}
	else
	{
		GpioOff(gpio);
	}
}

/*----------------- public -----------------*/
void DoConfig(void)
{
	GpioInit(PC7, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioOff(PC7);
}

bool DoGetValue(int i)
{
	switch(i)
	{
		case 1:
			return DoGet(PC7);
	}
	return false;
}

void DoSetValue(int i, bool value)
{
	switch(i)
	{
		case 1:
			DoSet(PC7, value);
			break;
	}
}
