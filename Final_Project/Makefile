#   Makefile
#   Version 
#   Author: WildfootW
#   GitHub: github.com/WildfootW
#   Copyright (C) 2019-2020 WildfootW All rights reserved.

COMPILE_MCU         := atmega328p
DUDE_MCU            := m328p
DUDE_USB_PORT       := /dev/ttyS8 # Your Serial Port
PROGRAMMER          := stk500v1 # ArduinoISP
PROGRAMMER_BAUD     := 19200 # 19200 for ArduinoISP stk500v1

F_CPU               := 1000000UL
#F_CPU               := 8000000UL
TARGET              := main
SRCS                := main ADConverter Millis ObstacleDetector RouteDetector Sensors SevenSegment WheelControl Usart
SRCOBJS             := $(addsuffix .o, $(SRCS))

CXX                 := avr-g++
AR                  := avr-ar
OBJCOPY             := avr-objcopy
OBJDUMP             := avr-objdump
AVRSIZE             := avr-size
AVRDUDE             := avrdude

CXXFLAGS_COMPILE    := -c -std=c++11 -Wall -Os -ffunction-sections -fdata-sections -mmcu=${COMPILE_MCU} -DF_CPU=${F_CPU} -DNDEBUG
CXXFLAGS_LINK       := -Os -mmcu=${COMPILE_MCU} -ffunction-sections -fdata-sections -Wl,--gc-sections

.PHONY: all
all: link size flash

.PHONY: link
link: $(SRCOBJS)
	$(CXX) ${CXXFLAGS_LINK} $^ -o ${TARGET}.elf

$(SRCOBJS): %.o: %.cpp
	${CXX} ${CXXFLAGS_COMPILE} $< -o $@

.PHONY: flash
flash:
	${OBJCOPY} -O ihex -R .eeprom ${TARGET}.elf ${TARGET}.ihex
	${AVRDUDE} -p ${DUDE_MCU} -c ${PROGRAMMER} -b ${PROGRAMMER_BAUD} -P ${DUDE_USB_PORT} -U flash:w:${TARGET}.ihex:i

.PHONY: size
size: ${TARGET}.elf
	${AVRSIZE} -C --mcu=${COMPILE_MCU} ${TARGET}.elf

.PHONY: clean
clean:
	rm -f *.o *.ihex *.elf

