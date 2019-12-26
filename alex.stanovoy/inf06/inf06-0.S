    .intel_syntax noprefix
    .text
    .global _start, bla
_start:
    mov     rax, 4
    mov     rbx, 1
    mov     rcx, offset format
    mov     rdx, 14
    int     0x80
    mov     rax, 1
    mov     ebx, 0
    int     0x80

    .data
format: .string "Hello, World!\n"
