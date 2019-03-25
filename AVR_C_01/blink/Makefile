#   Makefile
#   Version 
#   Author: WildfootW
#   GitHub: github.com/WildfootW
#   Copyright (C) 2019 WildfootW All rights reserved.

# compile
MCU_compiler=atmega328p
COMPILE_CCCFLAGS=-c -std=c99 -Wall -Os -ffunction-sections -fdata-sections -mmcu=${MCU_compiler} -F_CPU=${F_CPU}
LINK_CCCFLAGS=-Os -mmcu=${MCU_compiler} -ffunction-sections -fdata-sections -Wl,--gc-sections
CCC=avr-gcc
F_CPU=1200000

USB_PORT=/dev/ttyACM0
MCU_dude=m328p
OBJCOPY=avr-objcopy
PROGRAMMER=stk500v1 # ArduinoISP
PROGRAMMER_BAUD=19200 # 19200 for ArduinoISP stk500v1

TARGET=main
OBJ := test.o

all: link flash

link: $(OBJ)
	$(CCC) ${LINK_CCCFLAGS} $^ -o ${TARGET}.elf


$(OBJ): %.o: %.c
	${CCC} ${COMPILE_CCCFLAGS} $< -o $@
	

flash:
	${OBJCOPY} -O ihex -R .eeprom ${TARGET}.elf ${TARGET}.ihex
	avrdude -p ${MCU_dude} -c ${PROGRAMMER} -b ${PROGRAMMER_BAUD} -P ${USB_PORT} -U flash:w:${TARGET}.ihex:i

clean:
	rm -f *.o *.ihex *.elf
