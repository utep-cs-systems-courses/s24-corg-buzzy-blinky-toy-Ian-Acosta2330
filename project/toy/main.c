#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"


#define SW1 BIT3
#define SW2 BIT0
#define SW3 BIT1
#define SW4 BIT2
#define SW5 BIT3

//#define SWITCH_A SW1
//#define SWITCH_B SW2

//4 and 5 for sounds
#define SWITCH_L SW2, SW3, SW4, SW5
//#define SWITCH_S SW4, SW5
#define SWITCH_1 SW1

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;

  P2DIR |= LEDS;
  P2OUT &= ~LEDS;
  
  /*
  P2DIR |= LEDS
  P2OUT &= ~LEDS;
  */
  
  configureClocks();

  buzzer_init();
  
  P1REN |= SWITCH_1;
  P1IE |= SWITCH_1;
  P1OUT |= SWITCH_1;
  P1DIR &= ~SWITCH_1;
  
  P2REN |= SWITCH_L;
  P2IE |= SWITCH_L;
  P2OUT |= SWITCH_L;
  P2DIR &= ~SWITCH_L;

  or_sr(0x18);
}

void switch_interrupt_handler() {
  char p1val = P1IN;
  
  char p2val = P2IN;

  P1IES |= (p1val & SWITCH_1);
  P1IES &= (p1val | ~SWITCH_1);
  
  P2IES |= (p2val & SWITCH_L);
  P2IES &= (p2val | ~SWITCH_L);

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
    P2OUT |= LED_GREEN;
    P2OUT &= ~LED_RED;
    // buzzer_set_period(0);
  } else {
    P2OUT &= ~LED_GREEN;
    //buzzer_set_period(800);
  }
  
  if(p2val & SW3) {
    buzzer_set_period(0);
  }else {
    buzzer_set_period(800);
  }
  
  if(p2val & SW4) {
    buzzer_set_period(0);
  } else {
    buzzer_set_period(800);
  }

  if(p2val & SW5) {
    buzzer_set_period(0);
  } else {
    buzzer_set_period(1000);
  }
  
}

void __interrupt_vec(PORT1_VECTOR) Port_1() {
  if(P1IFG & SWITCH_1) {
    P1IFG &= ~SWITCH_1;
    switch_interrupt_handler();
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & SWITCH_L) {
    P2IFG &= ~SWITCH_L;
    switch_interrupt_handler();
  }
  
}
