#include "setup.h"

void assignRegisterValues(){

    DDRB    = 0b00000111;                   // PB0, PB1, PB2 as output (all other dont care or floating input)
    PORTB   = 0b00001000;                   // activate pull-up resistor for button on PB3
    PRR     = 0b00001010;                   // power saving measures
    ADCSRA  = 0b10000110;                   // enable ADC, prescaler = 64 @ 15,625Hz
        
    GIMSK |= (1 << PCIE);                   // set pin change interrupt enable
    PCMSK |= (1 << PCINT3);                 // set pin change interrupt for PB3 (button)
    MCUCR |= (1 << SE) | (1 << SM1);        // power-down mode enable
    ADMUX |= (1 << MUX1);                   // set ADC input to pin 2/PB4
    sei(); 



}