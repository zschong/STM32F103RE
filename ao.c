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
	AD5412_Type_t t = AD5412_Type_0_To_5_V;

	switch(type)
	{
		case Ao_Type_0_10_V:
			t = AD5412_Type_0_To_10_V;
			break;
		case Ao_Type_4_20_mA:
			t = AD5412_Type_4_To_20_mA;
			break;
	}

	switch(i)
	{
		case 1:
		case 2:
			break;
		case 3:
		case 4:
			AD5412_SetType(i-2, t);
			break;
	}
}
float AoGetValue(int i)
{
	uint16_t data = 0;

	switch(i)
	{
		case 1:
		case 2:
			data = DacGetValue(i);
			break;
		case 3:
		case 4:
			data = AD5412_GetValue(i-2)/2;
			break;
	}
	return ((data+1) * (10.0 / 4096.0));
}
void AoSetValue(int i, float value)
{
	uint16_t data = value * (4096.0 / 10.0) - 1;

	switch(i)
	{
		case 1:
		case 2:
			DacSetValue(i, data);
			break;
		case 3:
		case 4:
			AD5412_SetValue(i-2, data);
			break;
	}
	printf("AoSetValue(%d, %f)=%04X\n ", i, value, data);
}
