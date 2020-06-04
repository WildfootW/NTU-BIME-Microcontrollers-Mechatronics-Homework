; Assembly Code:

;;; Allow us to use names like "PORTB"
#define __SFR_OFFSET 0
	
#include   "avr/io.h"

start:
        SBI     DDRD, 5
blink:  LDI     r20, 250
        CALL    delay_n_ms
        SBI     PORTD, 5
        LDI     r20, 250
        CALL    delay_n_ms
        CBI     PORTD, 5
        JMP     blink

;;; Delay about r20*1ms.  Destroys r20, r30, and r31.
;;; One millisecond is about 16000 cycles at 16MHz.
;;; The basic loop takes about 5 cycles, so we need about 3000 loops.
delay_n_ms:
        LDI     31, (3000>>8)       ; high(3000)
        LDI     30, (3000&255)      ; low(3000)
delaylp:
        SBIW    r30, 1
        BRNE    delaylp
        SUBI    r20, 1
        BRNE    delay_n_ms
        RET
