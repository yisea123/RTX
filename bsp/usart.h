#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f10x_usart.h"

void uart_init(uint32_t argument);
void uart_send_datas(USART_TypeDef* USARTx, uint16_t num,uint8_t *datas);

#endif


