    .text
    .global main
main:
    push    {lr}
    loop:
    bl      getchar
    cmp     r0, #-1
    beq     loop_end
    cmp     r0, #48
    blt     loop
    cmp     r0, #57
    bgt     loop
    bl putchar
    b loop
    loop_end:
    mov     r0, #0
    pop     {pc}
