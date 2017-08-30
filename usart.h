#ifndef __USART_H__
#define __USART_H__
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

void UsartConfig(USART_TypeDef *usartx, int baud, int parity, int bsize, int stop);
uint32_t UsartSend(USART_TypeDef* usartx, char *buf, int len);
uint32_t UsartRecv(USART_TypeDef* usartx, char *buf, int len);

#endif//__USART_H__
