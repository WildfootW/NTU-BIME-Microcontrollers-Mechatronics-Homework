#define __SFR_OFFSET 0
#include <avr/io.h>

start:
; setup IO
        ldi     R24,    0b00000000
        out     DDRB,   R24 ; input
        ldi     R24,    0b11111111
        out     PORTB,  R24 ; pull-up
        out     DDRD,   R24 ; output
loop:   call    loop_func
        rjmp    loop

;   write in code
loop_func:
        ldi     R25,    0b00000000
        sbis    PINB,   0
        ldi     R25,    0b00111001
        sbis    PINB,   1
        ldi     R25,    0b01011110
        sbis    PINB,   2
        ldi     R25,    0b01111001
        sbis    PINB,   3
        ldi     R25,    0b01110001
        sbis    PINB,   4
        ldi     R25,    0b00111101
        sbis    PINB,   5
        ldi     R25,    0b01110111
        sbis    PINB,   6
        ldi     R25,    0b01111100
        com     R25
        out     PORTD,  R25
        ret


;   load data from array [TODO]
;loop_func:
;        ldi     R30,    lo8(character_array)
;        ldi     R31,    hi8(character_array)
;        ldd     R25,    Z + 17
;        sbis    PINB,   0
;        ldd     R25,    Z + 12
;        sbis    PINB,   1
;        ldd     R25,    Z + 13
;        sbis    PINB,   2
;        ldd     R25,    Z + 14
;        sbis    PINB,   3
;        ldd     R25,    Z + 15
;        sbis    PINB,   4
;        ldd     R25,    Z + 16
;        sbis    PINB,   5
;        ldd     R25,    Z + 10
;        sbis    PINB,   6
;        ldd     R25,    Z + 11
;        com     R25
;        out     PORTD,  R25
;        ret
;.type character_array, @object
;character_array:
;        .byte   63      ; (00) 0
;        .byte   6       ; (01) 1
;        .byte   91      ; (02) 2
;        .byte   79      ; (03) 3
;        .byte   102     ; (04) 4
;        .byte   109     ; (05) 5
;        .byte   125     ; (06) 6
;        .byte   7       ; (07) 7
;        .byte   127     ; (08) 8
;        .byte   111     ; (09) 9
;        .byte   119     ; (10) A
;        .byte   124     ; (11) b
;        .byte   57      ; (12) C
;        .byte   94      ; (13) d
;        .byte   121     ; (14) E
;        .byte   113     ; (15) F
;        .byte   61      ; (16) G
;        .byte   0       ; (17) off

