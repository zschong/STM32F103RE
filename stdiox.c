#include <stdio.h>
#include <stdarg.h>
#include "gpio.h"

int printfx(const char *fmt, ...)
{
	int ret = 0;
	va_list ap;
	uint32_t timeout = SystemCoreClock/1000;

	va_start(ap, fmt);
	GpioOn(PA11);
	ret = vfprintf(stdout, fmt, ap);
	while(timeout--);
	GpioOff(PA11);
	va_end(ap);

	return ret;
}
