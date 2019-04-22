#   Makefile
#   Version 
#   Author: WildfootW
#   GitHub: github.com/WildfootW
#   Copyright (C) 2019 WildfootW All rights reserved.

COMPILE_MCU         := atmega328p
DUDE_MCU            := m328p
DUDE_USB_PORT       := /dev/ttyACM0
PROGRAMMER          := stk500v1 # ArduinoISP
PROGRAMMER_BAUD     := 19200 # 19200 for ArduinoISP stk500v1

F_CPU               := 1000000UL
TARGET              := main
SRCS                := test
SRCOBJS             := $(addsuffix .o, $(SRCS))

#CCC                 := avr-gcc
CXX                 := avr-g++
AR                  := avr-ar
OBJCOPY             := avr-objcopy
OBJDUMP             := avr-objdump
AVRSIZE             := avr-size
AVRDUDE             := avrdude

#CCCFLAGS_COMPILE    := -c -std=c99 -Wall -Os -ffunction-sections -fdata-sections -mmcu=${COMPILE_MCU} -F_CPU=${F_CPU}
#CCCFLAGS_LINK       := -Os -mmcu=${COMPILE_MCU} -ffunction-sections -fdata-sections -Wl,--gc-sections
CXXFLAGS_COMPILE    := -c -std=c++14 -Wall -Os -ffunction-sections -fdata-sections -mmcu=${COMPILE_MCU} -F_CPU=${F_CPU}
CXXFLAGS_LINK       := -Os -mmcu=${COMPILE_MCU} -ffunction-sections -fdata-sections -Wl,--gc-sections

all: link flash

libs:

link: $(SRCOBJS)
	$(CXX) ${CXXFLAGS_LINK} $^ -o ${TARGET}.elf
#	$(CCC) ${CCCFLAGS_LINK} $^ -o ${TARGET}.elf


$(SRCOBJS): %.o: %.c
	${CXX} ${CXXFLAGS_COMPILE} $< -o $@
#	${CCC} ${CCCFLAGS_COMPILE} $< -o $@

flash:
	${OBJCOPY} -O ihex -R .eeprom ${TARGET}.elf ${TARGET}.ihex
	${AVRDUDE} -p ${DUDE_MCU} -c ${PROGRAMMER} -b ${PROGRAMMER_BAUD} -P ${DUDE_USB_PORT} -U flash:w:${TARGET}.ihex:i

clean:
	rm -f *.o *.ihex *.elf

size: ${TARGET}.elf
	${AVRSIZE} -C --mcu=${COMPILE_MCU} ${TARGET}.elf
