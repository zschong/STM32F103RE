#ifndef __DO_H__
#define __DO_H__
#include "gpio.h"

#define MAX_DO	1

void DoConfig(void);
bool DoGetValue(int i);
void DoSetValue(int i, bool value);

#endif//__DO_H__
