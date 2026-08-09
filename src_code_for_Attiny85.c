
#define F_CPU 1000000UL

#include <avr/io.h>         // standard AVR MC library
#include <util/delay.h>     // für delay function
#include <avr/sleep.h>      // für sleep mode
#include <avr/interrupt.h>  // für IRQs

// test comment


#define TWOHUNDOMILLI 200
#define QUARTERSECOND 250
#define HALFSECOND 500
#define ONESECOND 1000
#define TWOSECONDS 2000
#define THREESECONDS 3000

#define one     0b001001
#define two     0b001010
#define three   0b001011
#define four    0b001100
#define five    0b001101
#define six     0b001110
#define TIME    2800

uint8_t seed;
void outputRollNumber(uint8_t seed);    // function for outputting the light pattern for each roll
void flashingLights();


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


// -------------------------- main ------------------------------
int main(void) {

// ------configs ---------------------------------------------------------------------------

    DDRB    = 0b00000111;            // PB0, PB1, PB2 as output (all other dont care or floating input)
    PORTB   = 0b00001000;         // activate pull-up resistor for button on PB3
    PRR     = 0b00001010;          // power saving measures
    ADCSRA  = 0b10000110;         // enable ADC, prescaler = 64 @ 15,625Hz
    GIMSK |= (1 << PCIE);         // set pin change interrupt enable
    PCMSK |= (1 << PCINT3);      // set pin change interrupt for PB3 (button)
    MCUCR |= (1 << SE) | (1 << SM1);   // power-down mode enable
    ADMUX |= (1 << MUX1);       // set ADC input to pin 2/PB4
    sei(); 


    while (1)
    {

        sleep_mode();   // put the microcontroller to sleep until an interrupt occurs


    }

}
// ---- end main ------------------------------


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
