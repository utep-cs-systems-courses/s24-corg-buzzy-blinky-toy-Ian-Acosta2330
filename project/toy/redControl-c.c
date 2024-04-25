#include <msp430.h>
#include "led.h"
#include "libTimer.h"

#define SW2 BIT0

//volatile int dim = 4;

int redControl(int on) {
  int r = 0;
  /*if (on) {
    P1OUT |= LED_RED;
  }
  else {
    P1OUT &= ~LED_RED;
    }*/

  /*int dim = 4;
  
  if(dim > 0) {
    for(int i = 0; i < dim; i++) {
      redControl(1);
      __delay_cycles(50000);
      redControl(0);
      __delay_cycles(150000);
    }
    dim--;
  } else {
    dim = 4;
    }*/
  if(on) {
    P1OUT &= ~LED_RED;
  }

  if(!(on)) {
    P1OUT |= LED_RED;
    r = 1;
  }
  
  return r;
  
}

/*
void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if(P2IFG & SW2) {
    P2IFG &= ~SW2;
    if(dim > 0){
      for (int i = 0; i < dim; i++) {
	redControl(1);
	__delay_cycles(50000);
	redControl(0);
	__delay_cycles(150000);
      }
      dim--;
    }
    else {
      dim = 4;
    }
  }
}
*/

/*
int main(void) {
  P1DIR |= LED_RED;
  P1OUT &= ~LED_RED;

  P1REN |= SW2;
  P1OUT |= SW2;
  P1IE |= SW2;
  P1IES |= SW2;
  
  or_sr(0x18);

  while(1) {

  }

  return 0;
  
}*/

