#include <msp430.h>
#include "libTimer.h"
#include "led.h"

void blink(void) {
  P1DIR |= LEDS;
  
  configureClocks();
  enableWDTInterrupts();

  int a = 0;
  while(a < 25) {
      P1OUT &= ~LED_RED;
      __delay_cycles(800000);
      P1OUT |= LED_RED;
      __delay_cycles(800000);
      a++;
  }
  
  or_sr(0x18);
}
