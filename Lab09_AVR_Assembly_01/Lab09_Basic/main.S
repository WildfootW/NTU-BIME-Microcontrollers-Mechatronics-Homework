#define __SFR_OFFSET 0
#include <avr/io.h>

__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1

 .section .text.init,"ax",@progbits
.global init
 .type init, @function
init:
    ldi r24,lo8(-1)
    out DDRB,r24
    out DDRD,r24
    ret
 .size init, .-init

 .section .text.print_seven_segement,"ax",@progbits
.global print_seven_segement
 .type print_seven_segement, @function
print_seven_segement:
    com r22
    out PORTB,r22
    com r24
    out PORTD,r24
    ret
 .size print_seven_segement, .-print_seven_segement

 .section .text.startup.main,"ax",@progbits
.global main
 .type main, @function
main:
    call init
.L6:
    ldi r28,lo8(character_array)
    ldi r29,hi8(character_array)
.L4:
    ldi r16,lo8(character_array)
    ldi r17,hi8(character_array)
.L5:
    movw r30,r16
    ld r22,Z+
    movw r16,r30
    ld r24,Y
    call print_seven_segement
    ldi r31,lo8(1599999)
    ldi r18,hi8(1599999)
    ldi r24,hlo8(1599999)
1:  subi r31,1
    sbci r18,0
    sbci r24,0
    brne 1b
    rjmp .
    nop
    ldi r25,hi8(character_array+10)
    cpi r16,lo8(character_array+10)
    cpc r17,r25
    brne .L5
    adiw r28,1
    ldi r30,hi8(character_array+10)
    cpi r28,lo8(character_array+10)
    cpc r29,r30
    brne .L4
    rjmp .L6
 .size main, .-main

.global character_array
 .section .rodata.character_array,"a",@progbits
 .type character_array, @object
 .size character_array, 17
character_array:
    .byte 63
    .byte 6
    .byte 91
    .byte 79
    .byte 102
    .byte 109
    .byte 125
    .byte 7
    .byte 127
    .byte 111
    .byte 0
    .zero 6

.global __do_copy_data
