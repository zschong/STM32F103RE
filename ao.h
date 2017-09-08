#ifndef __AO_H__
#define __AO_H__
#include "spi.h"

#define AO_MAX			2

typedef enum
{
	AO_Cmd_Nop		= 0x00,
	AO_Cmd_Set		= 0x01,
	AO_Cmd_Get		= 0x02,
	AO_Cmd_Control	= 0x55,
	AO_Cmd_Reset	= 0x56,
}AOCmd_t;
typedef enum
{
	AO_Get_Status	= 0x00,
	AO_Get_Value	= 0x01,
	AO_Get_Control	= 0x02,
}AOGet_t;
typedef enum
{
	AO_Type_0_To_5_V = 0x00,		//+0  ~  +5V
	AO_Type_0_To_10_V = 0x01,		//+0  ~  +10V
	AO_Type_N5_To_P5_V = 0x02,		//-5  ~  +5V
	AO_Type_N10_To_P10_V = 0x03,	//-10 ~  +10V
	AO_Type_4_To_20_mA = 0x05,		//+4  ~  +20mA
	AO_Type_0_To_20_mA = 0x06,		//+0  ~  +20mA
	AO_Type_0_To_24_mA = 0x07,		//+0  ~  +24mA
}AOType_t;

void AoConfig(void);
void AoChipSelect(int i);
void AoChipUnselect(int i);

uint16_t AoReset(int i);
uint16_t AoGetStatus(int i);
uint16_t AoGetControl(int i);

float AoGetValue(int i);
void AoSetValue(int i, float value);
uint16_t AoSetType(int i, AOType_t type);

#endif//__AO_H__
