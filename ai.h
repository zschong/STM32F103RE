#ifndef __AI_H__
#define __AI_H__
#include "spi.h"

#define MAX_AI	8

void AiConfig(void);
void AiChipSelect(void);
void AiChipUnselect(void);
float AiGetValue(int i);

#endif//__AI_H__
