#include <asm/unistd_64.h>
#include <sys/syscall.h>

    .intel_syntax noprefix
    .text
    .global _start
_start:
    xor     esi, esi
    mov     eax, SYS_brk
    xor     ebx, ebx
    int     0x80
    mov     edi, eax
    push    edi
    .read_loop:
    test    esi, esi
    jne     .read_buff
    mov     esi, 1024
    add     edi, esi
    mov     eax, SYS_brk
    mov     ebx, edi
    int     0x80
    sub     edi, esi
    .read_buff:
    mov     eax, SYS_read
    xor     ebx, ebx
    mov     ecx, edi
    mov     edx, esi
    int     0x80
    test    eax, eax
    je      .write
    sub     esi, eax
    add     edi, eax
    jmp     .read_loop
    .write:
    mov     eax, '\n'
    mov     [edi], al
    .write_loop:
    mov     esi, edi    
    .find_next_loop:
    cmp     edi, [esp]
    je      .end
    dec     edi
    mov     al, '\n'
    cmp     [edi], al
    je      .write_line
    jmp     .find_next_loop
    .write_line:
    mov     eax, SYS_write
    mov     ebx, 1
    mov     ecx, edi
    inc     ecx
    mov     edx, esi
    sub     edx, edi
    int     0x80
    jmp     .write_loop
    .end:
    mov     eax, SYS_write
    mov     ebx, 1
    mov     ecx, edi
    mov     edx, esi
    sub     edx, edi
    inc     edx
    int     0x80
    mov     eax, SYS_brk
    imul    edi, -1
    mov     ebx, edi
    int     0x80
    pop     edi
    mov     eax, 1
    xor     ebx, ebx
    int     0x80
