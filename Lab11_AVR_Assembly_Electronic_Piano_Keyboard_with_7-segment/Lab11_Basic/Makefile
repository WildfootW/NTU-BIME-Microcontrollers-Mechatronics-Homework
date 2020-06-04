#   Makefile
#   Version 
#   Author: WildfootW
#   GitHub: github.com/WildfootW
#   Copyright (C) 2019 WildfootW All rights reserved.

# compile
MCU_compiler=atmega328p
ASSEMBLE_CCCFLAGS=-mmcu=${MCU_compiler} -nostartfiles
CCC=avr-gcc
F_CPU=8000000UL

# flash
USB_PORT=/dev/ttyS6
MCU_dude=m328p
OBJCOPY=avr-objcopy
PROGRAMMER=stk500v1 # ArduinoISP
PROGRAMMER_BAUD=19200 # 19200 for ArduinoISP stk500v1

TARGET=main
#SOURCES := main
SOURCES := blink

all: assemble flash

.PHONY: assemble
assemble:
	${CCC} ${ASSEMBLE_CCCFLAGS} ${SOURCES}.S -o ${TARGET}.out

.PHONY: flash
flash:
	${OBJCOPY} -O ihex -R .eeprom ${TARGET}.out ${TARGET}.ihex
	avrdude -p ${MCU_dude} -c ${PROGRAMMER} -b ${PROGRAMMER_BAUD} -P ${USB_PORT} -U flash:w:${TARGET}.ihex:i

.PHONY: clean
clean:
	-rm -f *.o *.ihex *.elf
