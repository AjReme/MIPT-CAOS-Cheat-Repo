	.text
	.global solve
solve:
	push {r5, r6}
	mov r5, #0
loop_begin:
	mov r6, r0
	mul r6, r5
	add r6, r1
	mul r6, r5
	add r6, r2
	mul r6, r5
	add r6, r3
	cmp r6, #0
	beq loop_end
	add r5, #1
	b loop_begin
loop_end:
	mov r0, r5
	pop {r5, r6}
	bx lr
