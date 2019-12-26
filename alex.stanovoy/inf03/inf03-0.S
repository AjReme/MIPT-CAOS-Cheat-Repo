    .data
input: .asciz "%d"
output: .asciz "%d\n"

    .text
    .global main
main:
    push    {lr}

    ldr     r0, =input
    sub     sp, #4
    mov     r1, sp
    bl      scanf
    ldr     r4, [sp]
    add     sp, #4

    ldr     r0, =input
    sub     sp, #4
    mov     r1, sp
    bl      scanf
    ldr     r5, [sp]
    add     sp, #4

    add     r1, r4, r5
    ldr     r0, =output
    bl      printf
    mov     r0, #0
    pop     {pc}
