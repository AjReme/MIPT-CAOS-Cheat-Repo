    .intel_syntax noprefix
    .text
    .global summ
summ:
    mov     eax, 0
    mov     edi, [esp+4]
    mov     esi, [esp+8]
    mov     edx, [esp+12]
    mov     ecx, [esp+16]
    .beg_loop:
    cmp     eax, edi
    je      .end_loop
    mov     ebx, [esi+4*eax]
    add     ebx, [edx+4*eax]
    mov     [ecx+4*eax], ebx
    inc     eax
    jmp     .beg_loop
    .end_loop:
    ret
