#include "keythread.h"   
 
uint8_t key0_pressed = 0;
uint8_t key1_pressed = 0;

void key_thread (void const *argument);                             // thread function

osThreadId key_thread_id;                                          // thread id
osThreadDef (key_thread, osPriorityHigh, 1, 0);                   // thread object

int Init_key_thread (void) {

  key_thread_id = osThreadCreate (osThread(key_thread), NULL);
  if (!key_thread_id) return(-1);
  
  return(0);
}

void key_thread (void const *argument) {
	KEY_Init();
  while (1) 
	{
		osSignalWait(0x01,osWaitForever);	
		if(key0_press_falg)
		{
			key0_press_falg = 0;
			osDelay(20);
			if(KEY0 == 0)
			{
				key0_pressed = 1;
			}
		}
		if(key1_press_falg)
		{
			key1_press_falg = 0;
			osDelay(20);
			if(KEY1 == 0)
			{
				key1_pressed = 1;
			}
		}		
  }
}
