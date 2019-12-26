    .intel_syntax noprefix
    .data
format: .string "%d"
    .text
    .global summ, everyday795
summ:
    mov     eax, 0
    mov     edi, N
    mov     esi, A
    mov     edx, B
    mov     ecx, R
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
everyday795:
    sub     esp, 4
    mov     esi, esp
    push    esp
    push    offset format
    call    scanf
    add     esp, 12

    mov     esi, [esi]
    imul    esi, [esp+4]
    add     esi, [esp+8]

    push    esi
    push    offset format
    call    printf
    add     esp, 8

    ret
