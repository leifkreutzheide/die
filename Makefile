
MCU     = attiny85
F_CPU   = 1000000UL
CC      = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
PORT    = /dev/ttyUSB0
PROGRAMMER = arduinoisp
BAUD    = 19200

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall

SRCS    = main.c setup.c functions.c
OBJS    = $(SRCS:.c=.o)

all: main.hex

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

main.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.hex: main.elf
	$(OBJCOPY) -O ihex $< $@

flash: main.hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) \
	-U flash:w:$<

fuses:
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) \
	-U lfuse:w:0xE2:m \
	-U hfuse:w:0xD5:m \
	-U efuse:w:0xFF:m

clean:
	rm -f *.o *.elf *.hex