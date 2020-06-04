	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.text.initial,"ax",@progbits
.global	initial
	.type	initial, @function
initial:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	out 0x4,__zero_reg__
	ldi r24,lo8(-1)
	out 0x5,r24
	out 0xa,r24
	ret
	.size	initial, .-initial
	.section	.text.print_seven_segement,"ax",@progbits
.global	print_seven_segement
	.type	print_seven_segement, @function
print_seven_segement:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	com r24
	out 0xb,r24
	ret
	.size	print_seven_segement, .-print_seven_segement
	.section	.text.check_status,"ax",@progbits
.global	check_status
	.type	check_status, @function
check_status:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r24,0
	ldi r25,0
.L6:
	in r18,0x3
	ldi r19,0
	com r18
	com r19
	mov r0,r24
	rjmp 2f
	1:
	asr r19
	ror r18
	2:
	dec r0
	brpl 1b
	sbrc r18,0
	rjmp .L5
	adiw r24,1
	cpi r24,8
	cpc r25,__zero_reg__
	brne .L6
	ldi r24,lo8(-1)
.L5:
	ret
	.size	check_status, .-check_status
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	call initial
	ldi r28,lo8(-125)
	ldi r29,lo8(-120)
	ldi r17,lo8(-62)
	ldi r16,lo8(-114)
	ldi r24,lo8(-122)
	mov r15,r24
	ldi r25,lo8(-95)
	mov r14,r25
	ldi r18,lo8(-58)
	mov r13,r18
	clr r12
	dec r12
.L11:
	call check_status
	mov __tmp_reg__,r24
	lsl r0
	sbc r25,r25
	sbc r26,r26
	sbc r27,r27
	movw r30,r24
	adiw r30,1
	cpi r30,8
	cpc r31,__zero_reg__
	brsh .L11
	subi r30,lo8(-(gs(.L13)))
	sbci r31,hi8(-(gs(.L13)))
	jmp __tablejump2__
	.section	.progmem.gcc_sw_table.main,"a",@progbits
	.p2align	1
.L13:
	.word gs(.L12)
	.word gs(.L14)
	.word gs(.L15)
	.word gs(.L16)
	.word gs(.L17)
	.word gs(.L18)
	.word gs(.L19)
	.word gs(.L20)
	.section	.text.startup.main
.L12:
	out 0xb,r12
	rjmp .L11
.L14:
	out 0xb,r13
	rjmp .L11
.L15:
	out 0xb,r14
	rjmp .L11
.L16:
	out 0xb,r15
	rjmp .L11
.L17:
	out 0xb,r16
	rjmp .L11
.L18:
	out 0xb,r17
	rjmp .L11
.L19:
	out 0xb,r29
	rjmp .L11
.L20:
	out 0xb,r28
	rjmp .L11
	.size	main, .-main
.global	character_array
	.section	.rodata.character_array,"a",@progbits
	.type	character_array, @object
	.size	character_array, 18
character_array:
	.byte	63
	.byte	6
	.byte	91
	.byte	79
	.byte	102
	.byte	109
	.byte	125
	.byte	7
	.byte	127
	.byte	111
	.byte	119
	.byte	124
	.byte	57
	.byte	94
	.byte	121
	.byte	113
	.byte	61
	.byte	0
	.ident	"GCC: (GNU) 5.4.0"
.global __do_copy_data
