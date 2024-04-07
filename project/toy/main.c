#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"

#define SW1 BIT3
#define SWITCHES SW1

void main(void) {
  configureClocks();

  buzzer_init();
  
  P1DIR |= LEDS; //setup the leds
  
  P1OUT &= ~LEDS; //turn off red led
  
  P1REN |= SWITCHES;
  P1IE |= SWITCHES;
  P1OUT |= SWITCHES;
  P1DIR &= ~SWITCHES;
  
  or_sr(0x18);
}

void switch_interrupt_handler() {
  char p1val = P1IN;

  P1IES |= (p1val & SWITCHES);
  P1IES &= (p1val | ~SWITCHES);

  /*
  if(p1val & SW2) {
    P1OUT |= LED_RED;
    P1OUT |= LED_GREEN;
    }*/
  
  if (p1val & SW1) {
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    buzzer_set_period(0);
  } else {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    buzzer_set_period(1000);
  }
}

void __interrupt_vec(PORT1_VECTOR) Port_1() {
  if(P1IFG & SWITCHES) {
    P1IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
