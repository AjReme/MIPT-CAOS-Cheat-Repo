	.text
	.global summ
summ:
loop_begin:
	cmp r1, #0
	beq loop_end
	ldr r3, [r2]
	add r0, r3
	add r2, #4
	sub r1, #1
	b loop_begin
loop_end:
	bx lr
