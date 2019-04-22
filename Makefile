#   Makefile
#   Version 
#   Author: WildfootW
#   GitHub: github.com/WildfootW
#   Copyright (C) 2019 WildfootW All rights reserved.

# compile
COMPILE_MCU         := atmega328p
#COMPILE_CCCFLAGS    := -c -std=c99 -Wall -Os -ffunction-sections -fdata-sections -mmcu=${COMPILE_MCU} -F_CPU=${F_CPU}
#LINK_CCCFLAGS       := -Os -mmcu=${COMPILE_MCU} -ffunction-sections -fdata-sections -Wl,--gc-sections
COMPILE_CCCFLAGS    := -c -std=c++14 -Wall -Os -ffunction-sections -fdata-sections -mmcu=${COMPILE_MCU} -F_CPU=${F_CPU}
LINK_CCCFLAGS       := -Os -mmcu=${COMPILE_MCU} -ffunction-sections -fdata-sections -Wl,--gc-sections

#CCC                 := avr-gcc
CXX                 := avr-g++
AR                  := avr-ar
OBJCOPY             := avr-objcopy
OBJDUMP             := avr-objdump
AVRSIZE             := avr-size
AVRDUDE             := avrdude

F_CPU               := 1000000UL
BAUD                := 9600UL

USB_PORT            := /dev/ttyACM0
dude_arg_MCU        := m328p
PROGRAMMER          := stk500v1 # ArduinoISP
PROGRAMMER_BAUD     := 19200 # 19200 for ArduinoISP stk500v1

TARGET              := main
SRCS                := test
SRCOBJS             := $(addsuffix .o, $(SRCS))

all: link flash

libs:

link: $(SRCOBJS)
	$(CXX) ${LINK_CXXFLAGS} $^ -o ${TARGET}.elf
#	$(CCC) ${LINK_CCCFLAGS} $^ -o ${TARGET}.elf


$(SRCOBJS): %.o: %.c
	${CXX} ${COMPILE_CXXFLAGS} $< -o $@
#	${CCC} ${COMPILE_CCCFLAGS} $< -o $@

flash:
	${OBJCOPY} -O ihex -R .eeprom ${TARGET}.elf ${TARGET}.ihex
	${AVRDUDE} -p ${dude_arg_MCU} -c ${PROGRAMMER} -b ${PROGRAMMER_BAUD} -P ${USB_PORT} -U flash:w:${TARGET}.ihex:i

clean:
	rm -f *.o *.ihex *.elf

size: ${TARGET}.elf
	${AVRSIZE} -C --mcu=${COMPILE_MCU} ${TARGET}.elf
