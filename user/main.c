/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "ledthread.h"  
#include "uartsendthread.h"   
#include "uartreceivethread.h"   
#include "virtualtimerthread.h"   

#include "uarttestthread.h"   

osThreadId main_id; //create the thread handle

/*
 * main: initialize and start the system
 */
int main (void) {
	main_id = osThreadGetId ();  // Read the Thread-ID of the main thread 
  osKernelInitialize ();                    // initialize CMSIS-RTOS
  // initialize peripherals here
	Init_led_thread ();
	Init_virtualtimer_thread ();
	Init_uart_receive_thread (1);
	Init_uart_send_thread (1);
	Init_uart_test_thread ();
  // create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);
  osKernelStart ();                         // start thread execution
}
