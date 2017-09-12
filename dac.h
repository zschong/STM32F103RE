#ifndef __DAC_H__
#define __DAC_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

void DacConfig(void);
uint16_t DacGetValue(int i);
void DacSetValue(int i, uint16_t value);


#endif//__DAC_H__
