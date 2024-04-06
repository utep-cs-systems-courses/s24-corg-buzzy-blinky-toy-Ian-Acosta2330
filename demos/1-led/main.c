//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;

  //Original code only turned on green led
  //After adjusting the led.h file, now its working correctly
  P1OUT &= ~LED_GREEN; //SHOULD turn off green
  P1OUT |= LED_RED;  //SHOULD turn on red

  /*
    // Something I used to test LEDS
  P1OUT &= ~LED_RED;
  
  while(1) {
    P1OUT ^= LED_GREEN;
    __delay_cycles(1000000);
  }
  */
  or_sr(0x18);		/* CPU off, GIE on */
}
