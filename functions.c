#include "functions.h"
#include "setup.h"





void outputRollNumber(uint8_t seed) {
    if      (seed < 43)  { flashingLights(); PORTB = one;   } 
    else if (seed < 86)  { flashingLights(); PORTB = two;   } 
    else if (seed < 128) { flashingLights(); PORTB = three; }
    else if (seed < 170) { flashingLights(); PORTB = four;  }
    else if (seed < 213) { flashingLights(); PORTB = five;  }
    else                 { flashingLights(); PORTB = six;   }
    _delay_ms(TIME);
    PORTB   = 0b00001000;                       // activate pull-up resistor for button on PB3 AND turn off all LEDs
}


void flashingLights(){
    _delay_ms(TWOHUNDOMILLI);
    PORTB = four;
    _delay_ms(TWOHUNDOMILLI);
    PORTB = one;
    _delay_ms(TWOHUNDOMILLI);
    PORTB = four;
    _delay_ms(TWOHUNDOMILLI);
    PORTB = one;
    _delay_ms(TWOHUNDOMILLI);
    PORTB = two;
    _delay_ms(TWOHUNDOMILLI);
    PORTB = one;
    _delay_ms(QUARTERSECOND);
    PORTB = three;
    _delay_ms(QUARTERSECOND);
    PORTB = one;
    _delay_ms(QUARTERSECOND);
    PORTB = two;
    _delay_ms(HALFSECOND);
}
