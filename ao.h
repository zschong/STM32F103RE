#ifndef __AO_H__
#define __AO_H__
#include "spi.h"

typedef enum
{
	Ao_Type_0_10_V,
	Ao_Type_4_20_mA,
}AoType_t;

void AoConfig(void);
void AoSetType(int i, AoType_t type);
float AoGetValue(int i);
void AoSetValue(int i, float value);

#endif//__AO_H__
