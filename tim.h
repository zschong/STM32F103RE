#ifndef __TIM_H__
#define __TIM_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

void PwmConfig(TIM_TypeDef* tim,  int period, int prescaler, int pulse, int channel);

#endif//__TIM_H__
