#include "uartthread.h"   

//*************************************************************************************************************//
osPoolId  uart_send_mpool;
osPoolDef(uart_send_mpool, 1, uart_msg_t);																		//define memory pool

osMessageQId  uart_send_queue;
osMessageQDef(uart_send_queue, 1, uart_msg_t);															//define message queue

osPoolId  uart_receive_mpool;
osPoolDef(uart_receive_mpool, 1, uart_msg_t);																		//define memory pool

osMessageQId  uart_receive_queue;
osMessageQDef(uart_receive_queue, 1, uart_msg_t);															//define message queue

osThreadId uart1_send_thread_id;                                          // thread id
osThreadId uart2_send_thread_id;                                          // thread id
osThreadId uart3_send_thread_id;                                          // thread id
osThreadId uart4_send_thread_id;                                          // thread id
osThreadId uart5_send_thread_id;                                          // thread id

osThreadId uart1_receive_thread_id;                                          // thread id
osThreadId uart2_receive_thread_id;                                          // thread id
osThreadId uart3_receive_thread_id;                                          // thread id
osThreadId uart4_receive_thread_id;                                          // thread id
osThreadId uart5_receive_thread_id;                                          // thread id
osThreadId current_uart_receive_thread_id;                                   // thread id

osThreadDef (uart_send_thread, osPriorityAboveNormal, 1, 0);                   // thread object
osThreadDef (uart_receive_thread, osPriorityAboveNormal, 1, 0);                   // thread object

uint8_t uart_frame_start=1;
uint8_t uart_receive_timerstart = 0;
uint8_t uart_receive_timecount = 0;
uint8_t uart_receive_overtime = 0;
uint16_t uart_receive_datacount=0;

//*************************************************************************************************************//
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

void uart_send_datas(USART_TypeDef* USARTx, uint16_t num,uint8_t *datas)
{
	uint16_t i;
	for(i=0;i<num;i++)
	{
		USARTx->SR &= 0XFFBF; //clear TC flag
		USARTx->DR = *datas++;
		osSignalWait(0x01,osWaitForever);	
	}
}

//*************************************************************************************************************//
int Init_uart_receive_thread (uint32_t argument) {
	switch ((uint32_t)argument)
	{
		case 1:
			uart1_receive_thread_id = osThreadCreate (osThread(uart_receive_thread), (void *)argument);
			if (!uart1_receive_thread_id) return(-1);
			break;
		case 2:
			uart2_receive_thread_id = osThreadCreate (osThread(uart_receive_thread), (void *)argument);
			if (!uart2_receive_thread_id) return(-1);
			break;
		case 3:
			uart3_receive_thread_id = osThreadCreate (osThread(uart_receive_thread), (void *)argument);
			if (!uart3_receive_thread_id) return(-1);
			break;
		case 4:
			uart4_receive_thread_id = osThreadCreate (osThread(uart_receive_thread), (void *)argument);
			if (!uart4_receive_thread_id) return(-1);
			break;
		case 5:
			uart5_receive_thread_id = osThreadCreate (osThread(uart_receive_thread), (void *)argument);
			if (!uart5_receive_thread_id) return(-1);
			break;
	}
  return(0);
}

void uart_receive_thread (void const *argument) {
	USART_TypeDef* USARTx;
	uart_msg_t *uart_receive_msg;
	uart_init((uint32_t)argument);
	uart_receive_mpool = osPoolCreate(osPool(uart_receive_mpool));
  uart_receive_queue = osMessageCreate(osMessageQ(uart_receive_queue), NULL);
	switch ((uint32_t)argument)
	{
		case 1:
			USARTx = USART1;
			current_uart_receive_thread_id = uart1_receive_thread_id;
			break;
		case 2:
			USARTx = USART2;
			current_uart_receive_thread_id = uart2_receive_thread_id;
			break;
		case 3:
			USARTx = USART3;
			current_uart_receive_thread_id = uart3_receive_thread_id;
			break;
		case 4:
			USARTx = UART4;
			current_uart_receive_thread_id = uart4_receive_thread_id;
			break;
		case 5:
			USARTx = UART5;
			current_uart_receive_thread_id = uart5_receive_thread_id;
			break;
	}
  while (1) 
	{
		osSignalWait(0x01,osWaitForever);	
		uart_receive_timecount = 0;   //clear timer count
		if(uart_frame_start)//start a new frame
		{
			uart_frame_start = 0;
			uart_receive_msg = (uart_msg_t*)osPoolAlloc(uart_receive_mpool);											//Allocate a memory pool buffer
			uart_receive_msg->USARTx = USARTx;
		}
		if(uart_receive_overtime == 0)
		{
				if(uart_receive_datacount < UART_DATATEMP_SIZE)  //check received data num
				{
					uart_receive_msg->Datas[uart_receive_datacount++] = USART_ReceiveData(USARTx);	
				}
		}
		else   //stop receive data
		{
			uart_receive_msg->Datanum = uart_receive_datacount;
			uart_receive_datacount = 0;
			uart_frame_start = 1;
			uart_receive_overtime = 0;
			uart_receive_timerstart = 0;
			osMessagePut(uart_receive_queue, (uint32_t)uart_receive_msg, osWaitForever);				//Post pointer to memory pool buffer
		}
  }
}

//*************************************************************************************************************//
void USART1_IRQHandler(void)
{
	if(USART1->SR & 0X0020)
	{
		osSignalSet(uart1_receive_thread_id,0x01);
		uart_receive_timecount = 0;
		uart_receive_timerstart = 1;
		USART1->SR &= 0XFFDF;
	}
	if(USART1->SR & 0X0040)
	{
		osSignalSet(uart1_send_thread_id,0x01);
		USART1->SR &= 0XFFBF; //clear TC flag
	}
}	

void USART2_IRQHandler(void)
{
	if(USART2->SR & 0X0020)
	{
		osSignalSet(uart2_receive_thread_id,0x01);
		uart_receive_timecount = 0;
		uart_receive_timerstart = 1;
		USART2->SR &= 0XFFDF;
	}
	if(USART2->SR & 0X0040)
	{
		osSignalSet(uart2_send_thread_id,0x01);
		USART2->SR &= 0XFFBF; //clear TC flag
	}
}	

void USART3_IRQHandler(void)
{
	if(USART3->SR & 0X0020)
	{
		osSignalSet(uart3_receive_thread_id,0x01);
		uart_receive_timecount = 0;
		uart_receive_timerstart = 1;
		USART3->SR &= 0XFFDF;
	}
	if(USART3->SR & 0X0040)
	{
		osSignalSet(uart3_send_thread_id,0x01);
		USART3->SR &= 0XFFBF; //clear TC flag
	}
}	

void UART4_IRQHandler(void)
{
	if(UART4->SR & 0X0020)
	{
		osSignalSet(uart4_receive_thread_id,0x01);
		uart_receive_timecount = 0;
		uart_receive_timerstart = 1;
		UART4->SR &= 0XFFDF;
	}
	if(UART4->SR & 0X0040)
	{
		osSignalSet(uart4_send_thread_id,0x01);
		UART4->SR &= 0XFFBF; //clear TC flag
	}
}	

void UART5_IRQHandler(void)
{
	if(UART5->SR & 0X0020)
	{
		osSignalSet(uart5_receive_thread_id,0x01);
		uart_receive_timecount = 0;
		uart_receive_timerstart = 1;
		UART5->SR &= 0XFFDF;
	}
	if(UART5->SR & 0X0040)
	{
		osSignalSet(uart5_send_thread_id,0x01);
		UART5->SR &= 0XFFBF; //clear TC flag
	}
}	

