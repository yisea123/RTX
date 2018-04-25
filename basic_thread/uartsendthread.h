#ifndef __UARTSENDTHREAD_H
#define __UARTSENDTHREAD_H	 

#include "usart.h"                                     
#include "cmsis_os.h"     

#define UART_DATATEMP_SIZE 200

typedef struct {
		USART_TypeDef* USARTx;
	  uint16_t Datanum;
    uint8_t Datas[UART_DATATEMP_SIZE];
} uart_msg_t;

extern osPoolId  uart_send_mpool;
extern osMessageQId  uart_send_queue;

int Init_uart_send_thread (uint32_t argument);

#endif
