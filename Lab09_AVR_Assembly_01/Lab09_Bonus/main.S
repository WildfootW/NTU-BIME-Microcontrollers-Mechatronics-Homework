__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1

    .section .text.init,"ax",@progbits
.global init
    .type init, @function
init:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
    ldi r24,lo8(-1)
    out 0x4,r24
    out 0xa,r24
    ldi r30,lo8(-127)
    ldi r31,0
    ld r24,Z
    ori r24,lo8(10)
    st Z,r24
    ldi r24,lo8(-24)
    ldi r25,lo8(3)
    sts 136+1,r25
    sts 136,r24
    ldi r30,lo8(111)
    ldi r31,0
    ld r24,Z
    ori r24,lo8(2)
    st Z,r24
    sei
    ret
    .size init, .-init

    .section .text.print_seven_segement,"ax",@progbits
.global print_seven_segement
    .type print_seven_segement, @function
print_seven_segement:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
    com r24
    out 0x5,r24
    ret
    .size print_seven_segement, .-print_seven_segement

    .section .text.print_multiplexed_seven_segement,"ax",@progbits
.global print_multiplexed_seven_segement
    .type print_multiplexed_seven_segement, @function
print_multiplexed_seven_segement:
    push r15
    push r16
    push r17
    push r28
    push r29
/* prologue: function */
/* frame size = 0 */
/* stack size = 5 */
.L__stack_usage = 5
    movw r30,r24
    ldi r18,0
    ldi r19,0
    ldi r20,lo8(10)
    ldi r28,lo8(1)
    ldi r29,0
    ldi r16,lo8(10)
    ldi r17,0
    clr r15
    dec r15
.L4:
    ldi r24,0
    ldi r25,0
    ldi r22,lo8(1)
    ldi r23,0
.L8:
    cp r24,r18
    cpc r25,r19
    breq .L10
    movw r26,r22
    mul r20,r26
    movw r22,r0
    mul r20,r27
    add r23,r0
    clr __zero_reg__
    adiw r24,1
    rjmp .L8
.L10:
    cp r30,r22
    cpc r31,r23
    brlo .L6
    movw r24,r28
    mov r0,r18
    rjmp 2f
    1:
    lsl r24
    2:
    dec r0
    brpl 1b
    out 0xb,r24
    movw r24,r30
    call __udivmodhi4
    movw r24,r22
    movw r22,r16
    call __udivmodhi4
    movw r26,r24
    subi r26,lo8(-(character_array))
    sbci r27,hi8(-(character_array))
    ld r24,X
    com r24
    out 0x5,r24
    ldi r24,lo8(1999)
    ldi r25,hi8(1999)
1: sbiw r24,1
    brne 1b
    rjmp .
    nop
    out 0x5,r15
.L6:
    subi r18,-1
    sbci r19,-1
    cpi r18,4
    cpc r19,__zero_reg__
    brne .L4
/* epilogue start */
    pop r29
    pop r28
    pop r17
    pop r16
    pop r15
    ret
    .size print_multiplexed_seven_segement, .-print_multiplexed_seven_segement

    .section .text.startup.main,"ax",@progbits
.global main
    .type main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
    call init
.L15:
    ldi r28,0
    ldi r29,0
.L14:
    sts timer1_millis,__zero_reg__
    sts timer1_millis+1,__zero_reg__
    sts timer1_millis+2,__zero_reg__
    sts timer1_millis+3,__zero_reg__
.L12:
    lds r24,timer1_millis
    lds r25,timer1_millis+1
    lds r26,timer1_millis+2
    lds r27,timer1_millis+3
    cpi r24,-24
    sbci r25,3
    cpc r26,__zero_reg__
    cpc r27,__zero_reg__
    brsh .L17
    movw r24,r28
    call print_multiplexed_seven_segement
    rjmp .L12
.L17:
    adiw r28,1
    cpi r28,100
    cpc r29,__zero_reg__
    brne .L14
    rjmp .L15
    .size main, .-main

    .section .text.__vector_11,"ax",@progbits
.global __vector_11
    .type __vector_11, @function
__vector_11:
    push r1
    push r0
    in r0,__SREG__
    push r0
    clr __zero_reg__
    push r24
    push r25
    push r26
    push r27
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 7 */
.L__stack_usage = 7
    lds r24,timer1_millis
    lds r25,timer1_millis+1
    lds r26,timer1_millis+2
    lds r27,timer1_millis+3
    adiw r24,1
    adc r26,__zero_reg__
    adc r27,__zero_reg__
    sts timer1_millis,r24
    sts timer1_millis+1,r25
    sts timer1_millis+2,r26
    sts timer1_millis+3,r27
/* epilogue start */
    pop r27
    pop r26
    pop r25
    pop r24
    pop r0
    out __SREG__,r0
    pop r0
    pop r1
    reti
    .size __vector_11, .-__vector_11
    .comm timer1_millis,4,1

.global character_array
    .section .rodata.character_array,"a",@progbits
    .type character_array, @object
    .size character_array, 11
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

.global __do_copy_data

.global __do_clear_bss
