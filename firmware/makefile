# makefile

MCU=atmega8
F_CPU = 16000000L

#For baud rate settigns, see should give an error of 0.2%. See p. 162 of the Atmega8 manual
BAUDRATE = 9600

# optimize for size:
CDEFS = -D F_CPU=$(F_CPU) -D BAUDRATE=$(BAUDRATE)

CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues $(CDEFS)
OBJCOPY=avr-objcopy
CC = avr-gcc
TARGET = wifi
OBJS = serial.o utils.o
SRCS = $(OBJS, .o=.c)

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).out
	$(OBJCOPY) -R .eeprom -O ihex $(TARGET).out $(TARGET).hex
	avr-size $(TARGET).hex
	
$(TARGET).out: main.c $(OBJS) hardware.h
	$(CC) main.c -o $(TARGET).out $(CFLAGS) -Wl,-Map,$(TARGET).map $(OBJS) -lm

serial.o: serial.c serial.h
	$(CC) $(CFLAGS) -c serial.c

utils.o: utils.c utils.h hardware.h
	$(CC) $(CFLAGS) -c utils.c

fuseload:
# the difference between high fuse bit 0xd9 and 0x59 is that the latter one
# sets PC6 as standard input/output pin, while the first one as reset
#sudo avrdude -p m8 -P usb -c avrisp2 -e -U lfuse:w:0xef:m -U hfuse:w:0xd9:m -U flash:w:$(TARGET).hex
#        sudo avrdude -p m8 -P usb -c avrisp2 -e -U lfuse:w:0xef:m -U hfuse:w:0x59:m -U flash:w:$(TARGET).hex                

readfuse:
	sudo avrdude -v -p m8 -P usb -c avrisp2 -U lfuse:r:lfuse.txt:r -U hfuse:r:hfuse.txt:r
	
read:
	sudo avrdude -v -p m8 -P usb -c avrisp2 -U flash:r:"flash.hex":r
	
readeeprom:
	sudo avrdude -v -p m8 -P usb -c avrisp2 -U eeprom:r:"eeprom.hex":r

load:
	sudo avrdude -p m8 -P usb -c avrisp2 -e -U flash:w:$(TARGET).hex -U lfuse:w:0xef:m -U hfuse:w:0xd9:m
	
# --------------------
	
clean:
	rm *.o *.map *.out *.hex *.*~ -rf
