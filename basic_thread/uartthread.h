#ifndef __UARTTHREAD_H
#define __UARTTHREAD_H	 

#include "usart.h"                                     
#include "cmsis_os.h"     

//*************************************************************************************************************//
#define UART_DATATEMP_SIZE 200

typedef struct {
		USART_TypeDef* USARTx;
	  uint16_t Datanum;
    uint8_t Datas[UART_DATATEMP_SIZE];
} uart_msg_t;

//*************************************************************************************************************//
extern osPoolId  uart_send_mpool;
extern osMessageQId  uart_send_queue;

int Init_uart_send_thread (uint32_t argument);
void uart_send_thread (void const *argument);                             // thread function
void uart_send_datas(USART_TypeDef* USARTx, uint16_t num,uint8_t *datas);

//*************************************************************************************************************//
extern uint8_t uart_receive_timecount;
extern uint8_t uart_receive_timerstart;
extern uint8_t uart_receive_overtime;

extern osThreadId current_uart_receive_thread_id;    

extern osPoolId  uart_receive_mpool;
extern osMessageQId  uart_receive_queue;

int Init_uart_receive_thread (uint32_t argument);
void uart_receive_thread (void const *argument);                             // thread function
//*************************************************************************************************************//

#endif
