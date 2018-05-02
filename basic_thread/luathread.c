#include "luathread.h"     

void lua_thread (void const *argument);                             // thread function

osThreadId lua_thread_id;                                          // thread id
osThreadDef (lua_thread, osPriorityNormal, 1, 1024);                   // thread object

int Init_lua_thread (void) {

  lua_thread_id = osThreadCreate (osThread(lua_thread), NULL);
  if (!lua_thread_id) return(-1);
  
  return(0);
}

void lua_thread (void const *argument) {
	current_key0_focus_thread_id = lua_thread_id;
  while (1) 
	{
		osSignalWait(0x01,osWaitForever);	
		lua_main();	
  }
}

