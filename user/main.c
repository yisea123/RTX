/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "bsp.h"
#include "ledthread.h"  

osThreadId main_id; //create the thread handle

/*
 * main: initialize and start the system
 */
int main (void) {
	main_id = osThreadGetId ();  // Read the Thread-ID of the main thread 
  osKernelInitialize ();                    // initialize CMSIS-RTOS
	bsp_Initialize ();
  // initialize peripherals here
	Init_led_thread ();
  // create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);

  osKernelStart ();                         // start thread execution
	while(1);
}
