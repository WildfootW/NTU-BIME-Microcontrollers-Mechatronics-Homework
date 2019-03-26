## Makefile
https://stackoverflow.com/questions/32413959/avr-gcc-with-arduino

```
avr-gcc -c
        -std=gnu99
        -Os
        -Wall
        -ffunction-sections -fdata-sections
        -mmcu=m328p
        -DF_CPU=16000000
```

avr-gcc -c -std=gnu99 -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p test.c -o test.o


```
avr-gcc -Os
        -mmcu=m328p
        -ffunction-sections -fdata-sections
        -Wl,--gc-sections
```
avr-gcc -Os -mmcu=atmega328p -ffunction-sections -fdata-sections -Wl,--gc-sections test.o -o test.elf

ArduinoISP

avr-objcopy -O ihex -R .eeprom test.elf test.ihex

avrdude -p m328p -c stk500v1 -b 19200 -P /dev/ttyACM0 -U flash:w:test.ihex:i


