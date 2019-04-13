# description
LED blink on PD0

## install
```
sudo apt install -y gcc-avr avrdude avr-libc
```

## compile
```
avr-gcc -c                  \
        -std=gnu99          \
        -Os                 \
        -Wall               \
        -ffunction-sections \
        -fdata-sections     \
        -mmcu=atmega328p    \
        test.c -o test.o
```

## link
```
avr-gcc -Os                 \
        -mmcu=atmega328p    \
        -ffunction-sections \
        -fdata-sections     \
        -Wl,--gc-sections   \
        test.o -o test.elf
```

## program
ArduinoISP

```
avr-objcopy -O ihex     \
            -R .eeprom  \
            test.elf test.ihex
```
```
avrdude -p m328p        \
        -c stk500v1     \
        -b 19200        \
        -P /dev/ttyACM0 \
        -U flash:w:test.ihex:i
```

## reference
https://stackoverflow.com/questions/32413959/avr-gcc-with-arduino

