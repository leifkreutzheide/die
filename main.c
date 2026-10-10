
#define F_CPU 1000000UL

#include "setup.h"
#include "functions.h"

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



int main(void) {


    while (1)
    {

        sleep_mode();   // put the microcontroller to sleep until an interrupt occurs


    }

}
