#ifndef setup.h
#define setup.h



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

    extern volatile uint8_t seed;


    void assignRegisterValues();
    

#endif