#include "bsp.h"

/**
  \fn          int32_t LED_Initialize (void)
  \brief       Initialize LEDs
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t bsp_Initialize (void) {
  uint32_t n;
	
	n = LED_Initialize ();

  return n;
}
