#include <stdio.h>
#include <stdarg.h>
#include "gpio.h"

int printfx(const char *fmt, ...)
{
	int ret = 0;
	va_list ap;
	char buf[512] = {0};

	va_start(ap, fmt);
	ret = vsprintf(buf, fmt, ap);
	va_end(ap);

	GpioOn(PA11);
//	for(int i = 0; i < 0x100; i++);
	printf("%s", buf);
	GpioOff(PA11);

	return ret;
}
