# NTU BIME Microcontrollers Mechatronics Homework
BIME Microcontrollers Mechatronics 2018/2019-2 semester Homework

# arduino-cli cheat sheet
```
arduino-cli core update-index
arduino-cli board list
arduino-cli core search uno
arduino-cli core install arduino:avr
arduino-cli core list
arduino-cli board list
```

## Makefile
```
all: upload

upload: compile
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno $(SKETCH)

compile:
	arduino-cli compile --fqbn arduino:avr:uno $(SKETCH)

clean:
```

# AVR-C
## Tools
```
sudo apt install gcc-avr binutils-avr avr-libc
sudo apt install gdb-avr
sudo apt install avrdude
```

## Makefile
```
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
SOURCES := main ClockPrescale
OBJS := $(patsubst %,%.o,$(SOURCES))

all: link flash

.PHONY: link
link: $(OBJS)
	$(CCC) ${LINK_CCCFLAGS} $^ -o ${TARGET}.elf

%.o: %.c
	${CCC} ${COMPILE_CCCFLAGS} $< -o $@

.PHONY: flash
flash:
	${OBJCOPY} -O ihex -R .eeprom ${TARGET}.elf ${TARGET}.ihex
	avrdude -p ${MCU_dude} -c ${PROGRAMMER} -b ${PROGRAMMER_BAUD} -P ${USB_PORT} -U flash:w:${TARGET}.ihex:i

.PHONY: clean
clean:
	-rm -f *.o *.ihex *.elf *.s
```

### Compile sources to asm
```
COMPILE_ASM_CCCFLAGS=-S -std=c11 -Wall -Os -ffunction-sections -fdata-sections -mmcu=${MCU_compiler} -DF_CPU=${F_CPU}
ASMS := $(patsubst %,%.s,$(SOURCES))

.PHONY: asm
asm: $(ASMS)

%.s: %.c
	${CCC} ${COMPILE_ASM_CCCFLAGS} $< -o $@
```

### avrdude
* `-U flash|eeprom|hfuse|lfuse|efuse:r|w|v:<filename>[:format]:`
    * `-U flash:w:main.ihex:i`

## Library
* References
    * jypma
        * [AvrLib](https://github.com/jypma/AvrLib)
        * [AvrLibDemo](https://github.com/jypma/AvrLibDemo)
    * [Electronics - C++ classes for I/O pin abstraction](https://electronics.stackexchange.com/questions/19057/c-classes-for-i-o-pin-abstraction)
    * [Objects? No, thanks! (Using C++ effectively on small systems)](https://www.embedded.com/objects-no-thanks-using-c-effectively-on-small-systems/)

