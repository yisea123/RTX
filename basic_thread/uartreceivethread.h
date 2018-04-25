#ifndef __UARTRECEIVETHREAD_H
#define __UARTRECEIVETHREAD_H	 

#include "usart.h"                                     
#include "cmsis_os.h"     

extern uint8_t uart_receive_timecount;
extern uint8_t uart_receive_timerstart;
extern uint8_t uart_receive_overtime;
extern osThreadId current_uart_receive_thread_id;    

extern osPoolId  uart_receive_mpool;
extern osMessageQId  uart_receive_queue;

int Init_uart_receive_thread (uint32_t argument);

#endif
