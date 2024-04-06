#ifndef led_included
#define led_included

#define LED_RED BIT6               // P1.6 not 0 to make it work; IA
#define LED_GREEN BIT0             // P1.0 not 6 to make it work; IA
#define LEDS (BIT6 | BIT0)

#endif // included
