#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"

#define SW1 BIT3
#define SW2 BIT3
//#define SW3 BIT2
//#define SW4 BIT3
#define SWITCH_A SW1
#define SWITCH_B SW2
//#define SWITCHES SW1, SW2, SW3, SW4

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;

  /*
  P2DIR |= LEDS
  P2OUT &= ~LEDS;
  */
  
  configureClocks();

  buzzer_init();
  
  P2DIR |= LEDS; //setup the leds
  P2OUT &= ~LEDS; //turn off red led

  P1REN |= SWITCH_A;
  P1IE |= SWITCH_A;
  P1OUT |= SWITCH_A;
  P1DIR &= ~SWITCH_A;
  
  P2REN |= SWITCH_B;
  P2IE |= SWITCH_B;
  P2OUT |= SWITCH_B;
  P2DIR &= ~SWITCH_B;

  or_sr(0x18);
}

void switch_interrupt_handler() {
  char p1val = P1IN;
  char p2val = P2IN;

  P1IES |= (p1val & SWITCH_A);
  P1IES &= (p1val | ~SWITCH_A);
  
  P2IES |= (p2val & SWITCH_B);
  P2IES &= (p2val | ~SWITCH_B);

  //S1 turns on red led
  if (p1val & SW1) {
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    //buzzer_set_period(0);
  } else {
    P1OUT &= ~LED_RED;
    P1OUT |= LED_GREEN;
    //buzzer_set_period(0);
  }
  
  if(p2val & SW2) {
    //P2OUT |= LED_GREEN;
    //P2OUT &= ~LED_RED;
    buzzer_set_period(0);
  } else {
    //P2OUT &= ~LED_GREEN;
    buzzer_set_period(800);
  }
  /*
  if(p2val & SW3) {
    buzzer_set_period(0);
  }else {
    buzzer_set_period(800);
  }
  
  if(p2val & SW4) {
    buzzer_set_period(0);
  } else {
    buzzer_set_period(1000);
  }*/
}

void __interrupt_vec(PORT1_VECTOR) Port_1() {
  if(P1IFG & SWITCH_A) {
    P1IFG &= ~SWITCH_A;
    switch_interrupt_handler();
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & SWITCH_B) {
    P2IFG &= ~SWITCH_B;
    switch_interrupt_handler();
  }
  
}
