    .text
    .global sort_by_age
sort_by_age:
    push    {r4,r5,r6,r7,r8,lr}
    mov     r3, #0
    outer_loop:
    cmp     r3, r0
    beq     end_outer_loop
    mov     r2, r3
    add     r4, r3, #1
    inner_loop:
    cmp     r4, r0
    beq     end_inner_loop
    mov     r5, #48
    mul     r5, r2
    add     r5, r1
    add     r5, #4
    ldrb    r5, [r5]
    mov     r6, #48
    mul     r6, r4
    add     r6, r1
    add     r6, #4
    ldrb    r6, [r6]
    cmp     r6, r5
    movlt   r2, r4
    add     r4, #1
    b       inner_loop
    end_inner_loop:
    mov     r5, #48
    mul     r5, r3
    add     r5, r1
    mov     r6, #48
    mul     r6, r2
    add     r6, r1
    mov     r2, #0
    swap_loop:
    ldr     r7, [r5]
    ldr     r8, [r6]
    eor     r7, r8
    eor     r8, r7
    eor     r7, r8
    str     r7, [r5]
    str     r8, [r6]
    add     r5, #4
    add     r6, #4
    add     r2, #1
    cmp     r2, #12
    bne     swap_loop
    add     r3, #1
    b       outer_loop
    end_outer_loop:
    pop     {r4,r5,r6,r7,r8,pc}
