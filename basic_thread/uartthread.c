#include "uartthread.h"   

//*************************************************************************************************************//
#ifdef USE_UART1
osPoolId  uart1_send_mpool;
osPoolDef(uart1_send_mpool, 1, uart_msg_t);																		//define memory pool
osMessageQId  uart1_send_queue;
osMessageQDef(uart1_send_queue, 1, uart_msg_t);															//define message queue
osPoolId  uart1_receive_mpool;
osPoolDef(uart1_receive_mpool, 1, uart_msg_t);																		//define memory pool
osMessageQId  uart1_receive_queue;
osMessageQDef(uart1_receive_queue, 1, uart_msg_t);															//define message queue
osThreadId uart1_send_thread_id;                                          // thread id
osThreadId uart1_receive_thread_id;                                          // thread id

uint8_t uart1_frame_start=1;
uint8_t uart1_receive_timerstart = 0;
uint8_t uart1_receive_timecount = 0;
uint8_t uart1_receive_overtime = 0;
uint16_t uart1_receive_datacount=0;
#endif

#ifdef USE_UART2
osPoolId  uart2_send_mpool;
osPoolDef(uart2_send_mpool, 1, uart_msg_t);																		//define memory pool
osMessageQId  uart2_send_queue;
osMessageQDef(uart2_send_queue, 1, uart_msg_t);															//define message queue
osPoolId  uart2_receive_mpool;
osPoolDef(uart2_receive_mpool, 1, uart_msg_t);																		//define memory pool
osMessageQId  uart2_receive_queue;
osMessageQDef(uart2_receive_queue, 1, uart_msg_t);															//define message queue
osThreadId uart2_send_thread_id;                                          // thread id
osThreadId uart2_receive_thread_id;                                          // thread id

uint8_t uart2_frame_start=1;
uint8_t uart2_receive_timerstart = 0;
uint8_t uart2_receive_timecount = 0;
uint8_t uart2_receive_overtime = 0;
uint16_t uart2_receive_datacount=0;
#endif

#ifdef USE_UART3
osPoolId  uart3_send_mpool;
osPoolDef(uart3_send_mpool, 1, uart_msg_t);																		//define memory pool
osMessageQId  uart3_send_queue;
osMessageQDef(uart3_send_queue, 1, uart_msg_t);															//define message queue
osPoolId  uart3_receive_mpool;
osPoolDef(uart3_receive_mpool, 1, uart_msg_t);																		//define memory pool
osMessageQId  uart3_receive_queue;
osMessageQDef(uart3_receive_queue, 1, uart_msg_t);															//define message queue
osThreadId uart3_send_thread_id;                                          // thread id
osThreadId uart3_receive_thread_id;                                          // thread id

uint8_t uart3_frame_start=1;
uint8_t uart3_receive_timerstart = 0;
uint8_t uart3_receive_timecount = 0;
uint8_t uart3_receive_overtime = 0;
uint16_t uart3_receive_datacount=0;
#endif

#ifdef USE_UART4
osPoolId  uart4_send_mpool;
osPoolDef(uart4_send_mpool, 1, uart_msg_t);																		//define memory pool
osMessageQId  uart4_send_queue;
osMessageQDef(uart4_send_queue, 1, uart_msg_t);															//define message queue
osPoolId  uart4_receive_mpool;
osPoolDef(uart4_receive_mpool, 1, uart_msg_t);																		//define memory pool
osMessageQId  uart4_receive_queue;
osMessageQDef(uart4_receive_queue, 1, uart_msg_t);															//define message queue
osThreadId uart4_send_thread_id;                                          // thread id
osThreadId uart4_receive_thread_id;                                          // thread id

uint8_t uart4_frame_start=1;
uint8_t uart4_receive_timerstart = 0;
uint8_t uart4_receive_timecount = 0;
uint8_t uart4_receive_overtime = 0;
uint16_t uart4_receive_datacount=0;
#endif

osThreadDef (uart_send_thread, osPriorityAboveNormal, UART_SEND_THREAD_NUM, 0);                   // thread object
osThreadDef (uart_receive_thread, osPriorityAboveNormal, UART_RECEIVE_THREAD_NUM, 0);                   // thread object

//*************************************************************************************************************//
int Init_uart_send_thread (uint32_t argument) {
	switch ((uint32_t)argument)
	{
		case 1:
			#ifdef USE_UART1
				uart1_send_thread_id = osThreadCreate (osThread(uart_send_thread), (void *)argument);
				if (!uart1_send_thread_id) return(-1);
		  #endif
			break;
		case 2:
			#ifdef USE_UART2
				uart2_send_thread_id = osThreadCreate (osThread(uart_send_thread), (void *)argument);
				if (!uart2_send_thread_id) return(-1);
			#endif
			break;
		case 3:
			#ifdef USE_UART3
				uart3_send_thread_id = osThreadCreate (osThread(uart_send_thread), (void *)argument);
				if (!uart3_send_thread_id) return(-1);
			#endif
			break;
		case 4:
			#ifdef USE_UART4
				uart4_send_thread_id = osThreadCreate (osThread(uart_send_thread), (void *)argument);
				if (!uart4_send_thread_id) return(-1);
			#endif
			break;
	}
  return(0);
}

void uart_send_thread (void const *argument) {
	USART_TypeDef* USARTx;
	osEvent evt;
	uart_init((uint32_t)argument);
	switch ((uint32_t)argument)
	{
		case 1:
			#ifdef USE_UART1
				USARTx = USART1;
				uart1_send_mpool = osPoolCreate(osPool(uart1_send_mpool));
				uart1_send_queue = osMessageCreate(osMessageQ(uart1_send_queue), NULL);
		  #endif
			break;
		case 2:
			#ifdef USE_UART2
				USARTx = USART2;
				uart2_send_mpool = osPoolCreate(osPool(uart2_send_mpool));
				uart2_send_queue = osMessageCreate(osMessageQ(uart2_send_queue), NULL);		
		  #endif
			break;
		case 3:
			#ifdef USE_UART3
				USARTx = USART3;
				uart3_send_mpool = osPoolCreate(osPool(uart3_send_mpool));
				uart3_send_queue = osMessageCreate(osMessageQ(uart3_send_queue), NULL);		
		  #endif
			break;
		case 4:
			#ifdef USE_UART4
				USARTx = UART4;
				uart4_send_mpool = osPoolCreate(osPool(uart4_send_mpool));
				uart4_send_queue = osMessageCreate(osMessageQ(uart4_send_queue), NULL);		
		  #endif
			break;
	}
  while (1) 
	{
		switch ((uint32_t)argument)
		{
			case 1:
				#ifdef USE_UART1
					evt = osMessageGet(uart1_send_queue, osWaitForever);						//wait for message to arrive
					if (evt.status == osEventMessage) {													//check we have received a message
						uart_msg_t *uart_send_msg = (uart_msg_t*)evt.value.p;
						if(uart_send_msg->USARTx == USARTx)
						{
							uart_send_datas(USARTx, uart_send_msg->Datanum,uart_send_msg->Datas);
							osPoolFree(uart1_send_mpool, uart_send_msg);															//Release the buffer
						}
					}
				#endif
				break;
			case 2:
				#ifdef USE_UART2
					evt = osMessageGet(uart2_send_queue, osWaitForever);						//wait for message to arrive
					if (evt.status == osEventMessage) {													//check we have received a message
						uart_msg_t *uart_send_msg = (uart_msg_t*)evt.value.p;
						if(uart_send_msg->USARTx == USARTx)
						{
							uart_send_datas(USARTx, uart_send_msg->Datanum,uart_send_msg->Datas);
							osPoolFree(uart2_send_mpool, uart_send_msg);															//Release the buffer
						}
					}
				#endif
				break;	
			case 3:
				#ifdef USE_UART3
					evt = osMessageGet(uart3_send_queue, osWaitForever);						//wait for message to arrive
					if (evt.status == osEventMessage) {													//check we have received a message
						uart_msg_t *uart_send_msg = (uart_msg_t*)evt.value.p;
						if(uart_send_msg->USARTx == USARTx)
						{
							uart_send_datas(USARTx, uart_send_msg->Datanum,uart_send_msg->Datas);
							osPoolFree(uart3_send_mpool, uart_send_msg);															//Release the buffer
						}
					}
				#endif
				break;		
			case 4:
				#ifdef USE_UART4
					evt = osMessageGet(uart4_send_queue, osWaitForever);						//wait for message to arrive
					if (evt.status == osEventMessage) {													//check we have received a message
						uart_msg_t *uart_send_msg = (uart_msg_t*)evt.value.p;
						if(uart_send_msg->USARTx == USARTx)
						{
							uart_send_datas(USARTx, uart_send_msg->Datanum,uart_send_msg->Datas);
							osPoolFree(uart4_send_mpool, uart_send_msg);															//Release the buffer
						}
					}
				#endif
				break;			
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
			#ifdef USE_UART1
				uart1_receive_thread_id = osThreadCreate (osThread(uart_receive_thread), (void *)argument);
				if (!uart1_receive_thread_id) return(-1);
			#endif
			break;
		case 2:
			#ifdef USE_UART2
				uart2_receive_thread_id = osThreadCreate (osThread(uart_receive_thread), (void *)argument);
				if (!uart2_receive_thread_id) return(-1);
			#endif
			break;
		case 3:
			#ifdef USE_UART3
				uart3_receive_thread_id = osThreadCreate (osThread(uart_receive_thread), (void *)argument);
				if (!uart3_receive_thread_id) return(-1);
			#endif
			break;
		case 4:
			#ifdef USE_UART4
				uart4_receive_thread_id = osThreadCreate (osThread(uart_receive_thread), (void *)argument);
				if (!uart4_receive_thread_id) return(-1);
		  #endif
			break;
	}
  return(0);
}

void uart_receive_thread (void const *argument) {
	USART_TypeDef* USARTx;
	uart_msg_t *uart_receive_msg;
	uart_init((uint32_t)argument);
	switch ((uint32_t)argument)
	{
		case 1:
			#ifdef USE_UART1
				USARTx = USART1;
				uart1_receive_mpool = osPoolCreate(osPool(uart1_receive_mpool));
				uart1_receive_queue = osMessageCreate(osMessageQ(uart1_receive_queue), NULL);
		  #endif
			break;
		case 2:
			#ifdef USE_UART2
				USARTx = USART2;
				uart2_receive_mpool = osPoolCreate(osPool(uart2_receive_mpool));
				uart2_receive_queue = osMessageCreate(osMessageQ(uart2_receive_queue), NULL);
			#endif
			break;
		case 3:
			#ifdef USE_UART3
				USARTx = USART3;
				uart3_receive_mpool = osPoolCreate(osPool(uart3_receive_mpool));
				uart3_receive_queue = osMessageCreate(osMessageQ(uart3_receive_queue), NULL);
		  #endif
			break;
		case 4:
			#ifdef USE_UART4
			USARTx = UART4;
			uart4_receive_mpool = osPoolCreate(osPool(uart4_receive_mpool));
      uart4_receive_queue = osMessageCreate(osMessageQ(uart4_receive_queue), NULL);
			#endif
			break;
	}
  while (1) 
	{
		switch ((uint32_t)argument)
		{
			case 1:
				#ifdef USE_UART1
					osSignalWait(0x01,osWaitForever);	
					uart1_receive_timecount = 0;   //clear timer count
					if(uart1_frame_start)//start a new frame
					{
						uart1_frame_start = 0;
						uart_receive_msg = (uart_msg_t*)osPoolAlloc(uart1_receive_mpool);											//Allocate a memory pool buffer
						uart_receive_msg->USARTx = USARTx;
					}
					if(uart1_receive_overtime == 0)
					{
							if(uart1_receive_datacount < UART_DATATEMP_SIZE)  //check received data num
							{
								uart_receive_msg->Datas[uart1_receive_datacount++] = USART_ReceiveData(USARTx);	
							}
					}
					else   //stop receive data
					{
						uart_receive_msg->Datanum = uart1_receive_datacount;
						uart1_receive_datacount = 0;
						uart1_frame_start = 1;
						uart1_receive_overtime = 0;
						uart1_receive_timerstart = 0;
						osMessagePut(uart1_receive_queue, (uint32_t)uart_receive_msg, osWaitForever);				//Post pointer to memory pool buffer
					}
				#endif
				break;
			case 2:
				#ifdef USE_UART2
					osSignalWait(0x01,osWaitForever);	
					uart2_receive_timecount = 0;   //clear timer count
					if(uart2_frame_start)//start a new frame
					{
						uart2_frame_start = 0;
						uart_receive_msg = (uart_msg_t*)osPoolAlloc(uart2_receive_mpool);											//Allocate a memory pool buffer
						uart_receive_msg->USARTx = USARTx;
					}
					if(uart2_receive_overtime == 0)
					{
							if(uart2_receive_datacount < UART_DATATEMP_SIZE)  //check received data num
							{
								uart_receive_msg->Datas[uart2_receive_datacount++] = USART_ReceiveData(USARTx);	
							}
					}
					else   //stop receive data
					{
						uart_receive_msg->Datanum = uart2_receive_datacount;
						uart2_receive_datacount = 0;
						uart2_frame_start = 1;
						uart2_receive_overtime = 0;
						uart2_receive_timerstart = 0;
						osMessagePut(uart2_receive_queue, (uint32_t)uart_receive_msg, osWaitForever);				//Post pointer to memory pool buffer
					}
				#endif
				break;	
			case 3:
				#ifdef USE_UART3
					osSignalWait(0x01,osWaitForever);	
					uart3_receive_timecount = 0;   //clear timer count
					if(uart3_frame_start)//start a new frame
					{
						uart3_frame_start = 0;
						uart_receive_msg = (uart_msg_t*)osPoolAlloc(uart3_receive_mpool);											//Allocate a memory pool buffer
						uart_receive_msg->USARTx = USARTx;
					}
					if(uart3_receive_overtime == 0)
					{
							if(uart3_receive_datacount < UART_DATATEMP_SIZE)  //check received data num
							{
								uart_receive_msg->Datas[uart3_receive_datacount++] = USART_ReceiveData(USARTx);	
							}
					}
					else   //stop receive data
					{
						uart_receive_msg->Datanum = uart3_receive_datacount;
						uart3_receive_datacount = 0;
						uart3_frame_start = 1;
						uart3_receive_overtime = 0;
						uart3_receive_timerstart = 0;
						osMessagePut(uart3_receive_queue, (uint32_t)uart_receive_msg, osWaitForever);				//Post pointer to memory pool buffer
					}
				#endif
				break;	
			case 4:
				#ifdef USE_UART4
					osSignalWait(0x01,osWaitForever);	
					uart4_receive_timecount = 0;   //clear timer count
					if(uart4_frame_start)//start a new frame
					{
						uart4_frame_start = 0;
						uart_receive_msg = (uart_msg_t*)osPoolAlloc(uart4_receive_mpool);											//Allocate a memory pool buffer
						uart_receive_msg->USARTx = USARTx;
					}
					if(uart4_receive_overtime == 0)
					{
							if(uart4_receive_datacount < UART_DATATEMP_SIZE)  //check received data num
							{
								uart_receive_msg->Datas[uart4_receive_datacount++] = USART_ReceiveData(USARTx);	
							}
					}
					else   //stop receive data
					{
						uart_receive_msg->Datanum = uart4_receive_datacount;
						uart4_receive_datacount = 0;
						uart4_frame_start = 1;
						uart4_receive_overtime = 0;
						uart4_receive_timerstart = 0;
						osMessagePut(uart4_receive_queue, (uint32_t)uart_receive_msg, osWaitForever);				//Post pointer to memory pool buffer
					}
				#endif
				break;						
		}
  }
}

//*************************************************************************************************************//
#ifdef USE_UART1
void USART1_IRQHandler(void)
{
	if(USART1->SR & 0X0020)
	{
		osSignalSet(uart1_receive_thread_id,0x01);
		uart1_receive_timecount = 0;
		uart1_receive_timerstart = 1;
		USART1->SR &= 0XFFDF;
	}
	if(USART1->SR & 0X0040)
	{
		osSignalSet(uart1_send_thread_id,0x01);
		USART1->SR &= 0XFFBF; //clear TC flag
	}
}	
#endif

#ifdef USE_UART2
void USART2_IRQHandler(void)
{
	if(USART2->SR & 0X0020)
	{
		osSignalSet(uart2_receive_thread_id,0x01);
		uart2_receive_timecount = 0;
		uart2_receive_timerstart = 1;
		USART2->SR &= 0XFFDF;
	}
	if(USART2->SR & 0X0040)
	{
		osSignalSet(uart2_send_thread_id,0x01);
		USART2->SR &= 0XFFBF; //clear TC flag
	}
}	
#endif

#ifdef USE_UART3
void USART3_IRQHandler(void)
{
	if(USART3->SR & 0X0020)
	{
		osSignalSet(uart3_receive_thread_id,0x01);
		uart3_receive_timecount = 0;
		uart3_receive_timerstart = 1;
		USART3->SR &= 0XFFDF;
	}
	if(USART3->SR & 0X0040)
	{
		osSignalSet(uart3_send_thread_id,0x01);
		USART3->SR &= 0XFFBF; //clear TC flag
	}
}	
#endif

#ifdef USE_UART4
void UART4_IRQHandler(void)
{
	if(UART4->SR & 0X0020)
	{
		osSignalSet(uart4_receive_thread_id,0x01);
		uart4_receive_timecount = 0;
		uart4_receive_timerstart = 1;
		UART4->SR &= 0XFFDF;
	}
	if(UART4->SR & 0X0040)
	{
		osSignalSet(uart4_send_thread_id,0x01);
		UART4->SR &= 0XFFBF; //clear TC flag
	}
}	
#endif

int SendChar(int ch)  
{  
    while(!(USART1->SR & USART_FLAG_TXE));  
    USART1->DR = (ch & 0x1FF);  
  
    return ch;  
}  
  
int GetKey(void)  
{  
    while(!(USART1->SR & USART_FLAG_RXNE));  
    return ((int)(USART1->DR & 0X1FF));  
} 

