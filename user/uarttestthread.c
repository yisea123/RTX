#include "uarttestthread.h"   
 
void uart_test_thread (void const *argument);                             // thread function


osThreadId uart_test_thread_id;                                          // thread id
osThreadDef (uart_test_thread, osPriorityNormal, 1, 0);                   // thread object

int Init_uart_test_thread (uint32_t argument) {

  uart_test_thread_id = osThreadCreate (osThread(uart_test_thread), (void *)argument);
  if (!uart_test_thread_id) return(-1);
  
  return(0);
}

void uart_test_thread (void const *argument) {
	uart_msg_t *uart_send_msg;
	osEvent evt;
	uint16_t i=0;
  while (1) 
	{
		switch ((uint32_t)argument)
		{
			case 1:
				#ifdef USE_UART1			
					evt = osMessageGet(uart1_receive_queue, osWaitForever);						//wait for message to arrive
					if (evt.status == osEventMessage) {													//check we have received a message
						uart_msg_t *uart_receive_msg = (uart_msg_t*)evt.value.p;
						uart_send_msg = (uart_msg_t*)osPoolAlloc(uart1_send_mpool);											//Allocate a memory pool buffer
						uart_send_msg->USARTx = uart_receive_msg->USARTx;
						uart_send_msg->Datanum = uart_receive_msg->Datanum;
						for(i=0;i<uart_send_msg->Datanum;i++)
						{
							uart_send_msg->Datas[i]=uart_receive_msg->Datas[i];
						}
						osPoolFree(uart1_receive_mpool, uart_receive_msg);															//Release the buffer
						osMessagePut(uart1_send_queue, (uint32_t)uart_send_msg, osWaitForever);				//Post pointer to memory pool buffer
					}
				#endif
				break;
			case 2:
				#ifdef USE_UART2			
					evt = osMessageGet(uart2_receive_queue, osWaitForever);						//wait for message to arrive
					if (evt.status == osEventMessage) {													//check we have received a message
						uart_msg_t *uart_receive_msg = (uart_msg_t*)evt.value.p;
						uart_send_msg = (uart_msg_t*)osPoolAlloc(uart2_send_mpool);											//Allocate a memory pool buffer
						uart_send_msg->USARTx = uart_receive_msg->USARTx;
						uart_send_msg->Datanum = uart_receive_msg->Datanum;
						for(i=0;i<uart_send_msg->Datanum;i++)
						{
							uart_send_msg->Datas[i]=uart_receive_msg->Datas[i];
						}
						osPoolFree(uart2_receive_mpool, uart_receive_msg);															//Release the buffer
						osMessagePut(uart2_send_queue, (uint32_t)uart_send_msg, osWaitForever);				//Post pointer to memory pool buffer
					}
				#endif
				break;
			case 3:
				#ifdef USE_UART3			
					evt = osMessageGet(uart3_receive_queue, osWaitForever);						//wait for message to arrive
					if (evt.status == osEventMessage) {													//check we have received a message
						uart_msg_t *uart_receive_msg = (uart_msg_t*)evt.value.p;
						uart_send_msg = (uart_msg_t*)osPoolAlloc(uart3_send_mpool);											//Allocate a memory pool buffer
						uart_send_msg->USARTx = uart_receive_msg->USARTx;
						uart_send_msg->Datanum = uart_receive_msg->Datanum;
						for(i=0;i<uart_send_msg->Datanum;i++)
						{
							uart_send_msg->Datas[i]=uart_receive_msg->Datas[i];
						}
						osPoolFree(uart3_receive_mpool, uart_receive_msg);															//Release the buffer
						osMessagePut(uart3_send_queue, (uint32_t)uart_send_msg, osWaitForever);				//Post pointer to memory pool buffer
					}
				#endif
				break;
			case 4:
				#ifdef USE_UART4			
					evt = osMessageGet(uart4_receive_queue, osWaitForever);						//wait for message to arrive
					if (evt.status == osEventMessage) {													//check we have received a message
						uart_msg_t *uart_receive_msg = (uart_msg_t*)evt.value.p;
						uart_send_msg = (uart_msg_t*)osPoolAlloc(uart4_send_mpool);											//Allocate a memory pool buffer
						uart_send_msg->USARTx = uart_receive_msg->USARTx;
						uart_send_msg->Datanum = uart_receive_msg->Datanum;
						for(i=0;i<uart_send_msg->Datanum;i++)
						{
							uart_send_msg->Datas[i]=uart_receive_msg->Datas[i];
						}
						osPoolFree(uart4_receive_mpool, uart_receive_msg);															//Release the buffer
						osMessagePut(uart4_send_queue, (uint32_t)uart_send_msg, osWaitForever);				//Post pointer to memory pool buffer
					}
				#endif
				break;					
		}
  }
}
