#define __SFR_OFFSET 0
#include <avr/io.h>

.section .text

.global start
start:
    ldi R20, 0b01010101
    out DDRD, R20
    out PORTD, R20
