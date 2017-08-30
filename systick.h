#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

uint32_t SystickConfig(void);
uint32_t GetTimeMSecond(void);
uint32_t GetTimeSecond(void);
uint32_t Timeout(uint32_t *last, uint32_t timeout);
void DelayMSecond(uint32_t ms);

#endif//__SYSTICK_H__
