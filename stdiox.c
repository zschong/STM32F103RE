#include <stdio.h>
#include <stdarg.h>
#include "gpio.h"

int printfx(const char *fmt, ...)
{
	int ret = 0;
	va_list ap;

	GpioOn(PA11);
	va_start(ap, fmt);
	ret = vfprintf(stdout, fmt, ap);
	va_end(ap);
	for(int i = 0; i < 1000; i++);
	GpioOff(PA11);

	return ret;
}
