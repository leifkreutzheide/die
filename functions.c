#include "functions.h"
#include "setup.h"



 ISR(PCINT0_vect)   // vector name depends on interrupt type
{
    

    if (!(PINB & (1 << PB3))) {                     // only proceed if pin is LOW (pressed)
        ADCSRA |= (1 << ADEN);                          // re-enable ADC
        for (uint8_t i = 0; i < 8; i++) {               // read LSB 8 times
            ADCSRA |= (1 << ADSC);                      // start conversion
            while (ADCSRA & (1 << ADSC));               // creating a mask over ADSC Bit to check if still converting
                seed = (seed << 1) | (ADC & 1);           // shift seed left, ADC marco that reads ADCL and ADCH correctly, uses (&1) mask to read just the LSB
    }

    ADCSRA &= ~(1 << ADEN);                       // disable ADC to save power
    outputRollNumber(seed);                       // output the result based on the seed
    }
}




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
