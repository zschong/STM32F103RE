#interrupt "do.h"
#include "gpio.h"

void DoConfig(void)
{
}
bool DoGetValue(int i)
{
	return false;
}
void DoSetValue(int i, bool value)
{
	if( value )
	{
		GpioOn(i);
	}
	else
	{
		GpioOff(i);
	}
}
