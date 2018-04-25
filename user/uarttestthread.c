#include "uarttestthread.h"   
 
void uart_test_thread (void const *argument);                             // thread function


osThreadId uart_test_thread_id;                                          // thread id
osThreadDef (uart_test_thread, osPriorityNormal, 1, 0);                   // thread object

int Init_uart_test_thread (void) {

  uart_test_thread_id = osThreadCreate (osThread(uart_test_thread), NULL);
  if (!uart_test_thread_id) return(-1);
  
  return(0);
}

void uart_test_thread (void const *argument) {
	uart_msg_t *uart_send_msg;
	uint16_t i=0;
  while (1) 
	{
		osEvent evt = osMessageGet(uart_receive_queue, osWaitForever);						//wait for message to arrive
		if (evt.status == osEventMessage) {													//check we have received a message
			uart_msg_t *uart_receive_msg = (uart_msg_t*)evt.value.p;
			uart_send_msg = (uart_msg_t*)osPoolAlloc(uart_send_mpool);											//Allocate a memory pool buffer
			uart_send_msg->USARTx = uart_receive_msg->USARTx;
			uart_send_msg->Datanum = uart_receive_msg->Datanum;
			for(i=0;i<uart_send_msg->Datanum;i++)
			{
				uart_send_msg->Datas[i]=uart_receive_msg->Datas[i];
			}
			osPoolFree(uart_receive_mpool, uart_receive_msg);															//Release the buffer
			osMessagePut(uart_send_queue, (uint32_t)uart_send_msg, osWaitForever);				//Post pointer to memory pool buffer
		}
  }
}
