#ifndef __SPI_H__
#define __SPI_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

void SPI1Config(void);
void SPI1SendWord(uint16_t word);
uint16_t SPI1ReadWord(void);

#endif//__SPI_H__
