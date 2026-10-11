# Pseudo-random electronic die with a linear voltage regulator and hardware debouncing

This project and this README is/will be broken up into 4 parts:

1. Schematic
2. Code and register setup 
3. Debounce design 
4. LDO voltage regulator 

---

### Schematic


### Registers used, and why

```c
    DDRB    = 0b00000111;              
    PORTB   = 0b00001000;             
    PRR     = 0b00001010;             
    ADCSRA  = 0b10000110;             
        
    GIMSK |= (1 << PCIE);              
    PCMSK |= (1 << PCINT3);            
    MCUCR |= (1 << SE) | (1 << SM1);     
    ADMUX |= (1 << MUX1);                
    sei(); 
```

| Register | Bit(s) | Reason |
|----------|----------|----------|
| DDRB     | 0-2     | Pins 0, 1 & 2 of port B are set to outputs, as these are the pins which the seven LEDs are connected to    |
| PORTB    | 3       | Port B pin 3 set to high to activate the pull-up resistor  |
| PRR      | 1, 3    | Here bits PRUSI and PRTIM1 are set to 1 to reduce clock related power consumption to periphery hardware (timers and serial interfaces). Important to note here is that bit 0 is not set, that would disable the ADC.  |
| ADCSRA   | 1, 2    | Setting bits [2:0] to 110 sets the division factor between the system clock frequency (1MHz) and the input clock to 64. This means the ADC input clock (derived from the CPU frequency) runs at $\frac{1\text{MHz}}{64} = 15.6 \text{kHz}$. This is below the reccomended range, poses no issue though, as I want the ADC readings to be noisy.  |
| GIMSK    | PCIE    | INT0 bit is NOT set, because a distinction between rising and falling edges is not needed. The PCIE bit enables pin-change-interrupts    |
| PCMSK    | PCINT3  | Here the *Pin Change Mask* Pin-Change-Interrupt pin 3 is enabled. This means pin 3 will trigger an interrupt.     |
| MCUCR    | SE, SM1 | Bit SE must be enabled for the MCU to enter sleep mode. Setting bits [SM1:SM0] to 10  enables the power-down sleep mode.    |
| ADMUX    | MUX1    |   Setting bits [MUX3:MUX0] to 0010 selects PB4 as our analog input (which is connected to the ADC).   |

sei() is a AVR specific function which sets *Global Interrupt Enable*


### Debounce design


### Regulator design





