#ifndef __KEYTHREAD_H
#define __KEYTHREAD_H	 

#include "key.h"                                     
#include "cmsis_os.h"     

extern osThreadId key_thread_id; 
extern uint8_t key0_pressed;
extern uint8_t key1_pressed;

int Init_key_thread (void);

#endif
