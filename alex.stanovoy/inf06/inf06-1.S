    .intel_syntax noprefix
    .data
buff: .byte 0

    .text
    .global _start
_start:
    .beg_loop:
    mov     rax, 3
    mov     rbx, 0
    mov     rcx, offset buff
    mov     rdx, 1
    int     0x80
    mov     r8, rax
    mov     rax, 4
    mov     rbx, 1
    mov     rcx, offset buff
    mov     rdx, r8
    int     0x80
    cmp     r8, 1
    je      .beg_loop
    mov     rax, 1
    mov     ebx, 0
    int     0x80
