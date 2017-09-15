#ifndef __DI_H__
#define __DI_H__
#include "gpio.h"

#define MAX_DI	4

void DiConfig(void);
bool DiGetValue(int i);

#endif//__DI_H__
