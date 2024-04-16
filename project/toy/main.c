#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"

#define NOTE_A 440
#define NOTE_B 494
#define NOTE_C 262
#define NOTE_D 294
#define NOTE_E 330
#define NOTE_F 349
#define NOTE_G 392

#define SW1 BIT3
#define SW2 BIT0
#define SW3 BIT1
#define SW4 BIT2
#define SW5 BIT3

//#define SWITCH_A SW1
//#define SWITCH_B SW2

//4 and 5 for sounds
//#define SWITCH_L (SW2 | SW3 | SW4 | SW5)
//#define SWITCH_S SW4, SW5
#define SWITCH_1 SW1

#define SWITCH_2 SW2
#define SWITCH_3 SW3
#define SWITCH_4 SW4
#define SWITCH_5 SW5

#define SWITCH_P2 (SWITCH_2 | SWITCH_3 | SWITCH_4 | SWITCH_5)

void zelda_lullaby() {
  buzzer_set_period(NOTE_G);
  __delay_cycles(500);
  buzzer_set_period(0);
}

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;

  P2DIR |= LEDS;
  P2OUT &= ~LEDS;

  P2DIR |= LEDS;
  P2OUT &= ~LEDS;
  
  configureClocks();

  buzzer_init();
  
  P1REN |= SWITCH_1;
  P1IE |= SWITCH_1;
  P1OUT |= SWITCH_1;
  P1DIR &= ~SWITCH_1;
  
  P2REN |= SWITCH_P2;
  P2IE |= SWITCH_P2;
  P2OUT |= SWITCH_P2;
  P2DIR &= ~SWITCH_P2;

  or_sr(0x18);
}

void switch_interrupt_handler() {
  char p1val = P1IN;

  P1IES |= (p1val & SWITCH_1);
  P1IES &= (p1val | ~SWITCH_1);
  
  //S1 turns on red led
  if (p1val & SWITCH_1) {
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    //  buzzer_set_period(0);
  } else {
    P1OUT &= ~LED_RED;
    P1OUT |= LED_GREEN;
    //  buzzer_set_period(1000);
  }
}

void switch_interrupt_handler_P2_2() {
  char p2val = P2IN;

  P2IES |= (p2val & SWITCH_2);
  P2IES &= (p2val | ~SWITCH_2);
  
  if(p2val & SW2) {
    buzzer_set_period(0);
    /* buzzer_set_period(NOTE_E);
    __delay_cycles(500);
    buzzer_set_period(NOTE_G);
    __delay_cycles(250);
    buzzer_set_period(NOTE_D);
    __delay_cycles(750);
    buzzer_set_period(0);*/
  } else {
    /*buzzer_set_period(NOTE_E);
    __delay_cycles(500);
    buzzer_set_period(NOTE_G);
    __delay_cycles(250);
    buzzer_set_period(NOTE_D);
    __delay_cycles(750);*/
    buzzer_set_period(800);
  }
}

void switch_interrupt_handler_P2_3() {
  char p2val = P2IN;
  P2IES |= (p2val & SWITCH_3);
  P2IES &= (p2val | ~SWITCH_3);
  if(p2val & SW3) {
    buzzer_set_period(0);
  } else {
    buzzer_set_period(1000);
  }
}

void switch_interrupt_handler_P2_4() {
  char p2val = P2IN;
  P2IES |= (p2val & SWITCH_4);
  P2IES &= (p2val | ~SWITCH_4);
  if (p2val & SW4) {
    buzzer_set_period(0);
  } else {
    buzzer_set_period(300);
  }
}

void switch_interrupt_handler_P2_5() {
  char p2val = P2IN;
  P2IES |= (p2val & SWITCH_5);
  P2IES &= (p2val | ~SWITCH_5);
  if(p2val & SW5) {
    buzzer_set_period(0);
  } else {
    buzzer_set_period(400);
  }
}

void __interrupt_vec(PORT1_VECTOR) Port_1() {
  if(P1IFG & SWITCH_1) {
    P1IFG &= ~SWITCH_1;
    switch_interrupt_handler();
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & SWITCH_2) {
    P2IFG &= ~SWITCH_2;
    switch_interrupt_handler_P2_2();
  }
  if (P2IFG & SWITCH_3) {
    P2IFG &= ~SWITCH_3;
    switch_interrupt_handler_P2_3();
  }
  if (P2IFG & SWITCH_4) {
    P2IFG &= ~SWITCH_4;
    switch_interrupt_handler_P2_4();
  }
  if(P2IFG & SWITCH_5) {
    P2IFG &= ~SWITCH_5;
    switch_interrupt_handler_P2_5();
  }
}
