#include "uartsendthread.h"   
 
osPoolId  uart_send_mpool;
osPoolDef(uart_send_mpool, 1, uart_msg_t);																		//define memory pool

osMessageQId  uart_send_queue;
osMessageQDef(uart_send_queue, 1, uart_msg_t);															//define message queue

void uart_send_thread (void const *argument);                             // thread function

osThreadId uart1_send_thread_id;                                          // thread id
osThreadId uart2_send_thread_id;                                          // thread id
osThreadId uart3_send_thread_id;                                          // thread id
osThreadId uart4_send_thread_id;                                          // thread id
osThreadId uart5_send_thread_id;                                          // thread id

osThreadDef (uart_send_thread, osPriorityAboveNormal, 1, 0);                   // thread object

int Init_uart_send_thread (uint32_t argument) {
	switch ((uint32_t)argument)
	{
		case 1:
			uart1_send_thread_id = osThreadCreate (osThread(uart_send_thread), (void *)argument);
			if (!uart1_send_thread_id) return(-1);
			break;
		case 2:
			uart2_send_thread_id = osThreadCreate (osThread(uart_send_thread), (void *)argument);
			if (!uart2_send_thread_id) return(-1);
			break;
		case 3:
			uart3_send_thread_id = osThreadCreate (osThread(uart_send_thread), (void *)argument);
			if (!uart3_send_thread_id) return(-1);
			break;
		case 4:
			uart4_send_thread_id = osThreadCreate (osThread(uart_send_thread), (void *)argument);
			if (!uart4_send_thread_id) return(-1);
			break;
		case 5:
			uart5_send_thread_id = osThreadCreate (osThread(uart_send_thread), (void *)argument);
			if (!uart5_send_thread_id) return(-1);
			break;
	}
  return(0);
}

void uart_send_thread (void const *argument) {
	USART_TypeDef* USARTx;
	uart_init((uint32_t)argument);
	uart_send_mpool = osPoolCreate(osPool(uart_send_mpool));
  uart_send_queue = osMessageCreate(osMessageQ(uart_send_queue), NULL);
	switch ((uint32_t)argument)
	{
		case 1:
			USARTx = USART1;
			break;
		case 2:
			USARTx = USART2;
			break;
		case 3:
			USARTx = USART3;
			break;
		case 4:
			USARTx = UART4;
			break;
		case 5:
			USARTx = UART5;
			break;
	}
  while (1) 
	{
		osEvent evt = osMessageGet(uart_send_queue, osWaitForever);						//wait for message to arrive
		if (evt.status == osEventMessage) {													//check we have received a message
			uart_msg_t *uart_send_msg = (uart_msg_t*)evt.value.p;
			if(uart_send_msg->USARTx == USARTx)
			{
				uart_send_datas(USARTx, uart_send_msg->Datanum,uart_send_msg->Datas);
				osPoolFree(uart_send_mpool, uart_send_msg);															//Release the buffer
			}
		}
  }
}

