#ifndef setup.h
#define setup.h
#endif


    #define F_CPU 1000000UL

    #include <avr/io.h>         // standard AVR MC library
    #include <util/delay.h>     // für delay function
    #include <avr/sleep.h>      // für sleep mode
    #include <avr/interrupt.h> // für IRQs


    #include <stdint.h>

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


    DDRB    = 0b00000111;                   // PB0, PB1, PB2 as output (all other dont care or floating input)
    PORTB   = 0b00001000;                   // activate pull-up resistor for button on PB3
    PRR     = 0b00001010;                   // power saving measures
    ADCSRA  = 0b10000110;                   // enable ADC, prescaler = 64 @ 15,625Hz
    
    
    
    GIMSK |= (1 << PCIE);                   // set pin change interrupt enable
    PCMSK |= (1 << PCINT3);                 // set pin change interrupt for PB3 (button)
    MCUCR |= (1 << SE) | (1 << SM1);        // power-down mode enable
    ADMUX |= (1 << MUX1);                   // set ADC input to pin 2/PB4
    sei(); 

uint8_t seed;
