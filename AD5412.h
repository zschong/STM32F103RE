#ifndef __AD5412_H__
#define __AD5412_H__
#include "spi.h"

#define AD5412_MAX			2

typedef enum
{
	AD5412_Cmd_Nop		= 0x00,
	AD5412_Cmd_Set		= 0x01,
	AD5412_Cmd_Get		= 0x02,
	AD5412_Cmd_Control	= 0x55,
	AD5412_Cmd_Reset	= 0x56,
}AD5412_Cmd_t;
typedef enum
{
	AD5412_Get_Status	= 0x00,
	AD5412_Get_Value	= 0x01,
	AD5412_Get_Control	= 0x02,
}AD5412_Get_t;
typedef enum
{
	AD5412_Type_0_To_5_V = 0x00,		//+0  ~  +5V
	AD5412_Type_0_To_10_V = 0x01,		//+0  ~  +10V
	AD5412_Type_N5_To_P5_V = 0x02,		//-5  ~  +5V
	AD5412_Type_N10_To_P10_V = 0x03,	//-10 ~  +10V
	AD5412_Type_4_To_20_mA = 0x05,		//+4  ~  +20mA
	AD5412_Type_0_To_20_mA = 0x06,		//+0  ~  +20mA
	AD5412_Type_0_To_24_mA = 0x07,		//+0  ~  +24mA
}AD5412_Type_t;

void AD5412_Config(void);
void AD5412_ChipSelect(int i);
void AD5412_ChipUnselect(int i);

void AD5412_Reset(int i);
void AD5412_SetType(int i, AD5412_Type_t type);
void AD5412_SetValue(int i, uint16_t value);

uint16_t AD5412_GetStatus(int i);
uint16_t AD5412_GetControl(int i);
uint16_t AD5412_GetValue(int i);


#endif//__AD5412_H__
