#include "ao.h"
#include "dac.h"
#include "AD5412.h"
#include "stdiox.h"

void AoConfig(void)
{
	DacConfig();
	AD5412_Config();
}
void AoSetType(int i, AoType_t type)
{
	switch(i)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			break;
	}
}
float AoGetValue(int i)
{
	uint16_t data = 0;

	switch(i)
	{
		case 0:
		case 1:
			data = DacGetValue(i);
			break;
		case 2:
		case 3:
			data = AD5412_GetValue(i-2);
			break;
	}
	return ((data+1) * (10.0 / 4096.0));
}
void AoSetValue(int i, float value)
{
	uint16_t data = value * (4096.0 / 10.0) - 1;

	switch(i)
	{
		case 0:
		case 1:
			DacSetValue(i, data);
			break;
		case 2:
		case 3:
			AD5412_SetValue(i-2, data);
			break;
	}
	printf("AoSetValue(%d, %f)=%04X\n ", i, value, data);
}
