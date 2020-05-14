#   Makefile
#   Version 
#   Author: WildfootW
#   GitHub: github.com/WildfootW
#   Copyright (C) 2019 WildfootW All rights reserved.

# compile
MCU_compiler=atmega328p
COMPILE_CCCFLAGS=-c -std=c11 -Wall -Os -ffunction-sections -fdata-sections -mmcu=${MCU_compiler} -DF_CPU=${F_CPU}
LINK_CCCFLAGS=-Os -mmcu=${MCU_compiler} -ffunction-sections -fdata-sections -Wl,--gc-sections
CCC=avr-gcc
F_CPU=1000000UL

# flash
USB_PORT=/dev/ttyS6
MCU_dude=m328p
OBJCOPY=avr-objcopy
PROGRAMMER=stk500v1 # ArduinoISP
PROGRAMMER_BAUD=19200 # 19200 for ArduinoISP stk500v1

TARGET=main
OBJS := main.o ClockPrescale.o

all: link flash

link: $(OBJS)
	$(CCC) ${LINK_CCCFLAGS} $^ -o ${TARGET}.elf

$(OBJS): %.o: %.c
	${CCC} ${COMPILE_CCCFLAGS} $< -o $@

flash:
	${OBJCOPY} -O ihex -R .eeprom ${TARGET}.elf ${TARGET}.ihex
	avrdude -p ${MCU_dude} -c ${PROGRAMMER} -b ${PROGRAMMER_BAUD} -P ${USB_PORT} -U flash:w:${TARGET}.ihex:i

clean:
	rm -f *.o *.ihex *.elf
