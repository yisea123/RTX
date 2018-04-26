#include "timeoutthread.h"   
 
void timeout_thread (void const *argument);                             // thread function

osThreadId timeout_thread_id;                                          // thread id
osThreadDef (timeout_thread, osPriorityHigh, 1, 0);                   // thread object

int Init_timeout_thread (void) {

  timeout_thread_id = osThreadCreate (osThread(timeout_thread), NULL);
  if (!timeout_thread_id) return(-1);
  
  return(0);
}

void timeout_thread (void const *argument) {
	TIM2_Int_Init();
  while (1) 
	{
		osSignalWait(0x01,osWaitForever);	
	  if(uart_receive_overtime)
		{
			osSignalSet(current_uart_receive_thread_id,0x01); //send the last signal
		}
  }
}
