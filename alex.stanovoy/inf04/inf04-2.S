    .intel_syntax noprefix
    .text
    .global mergesort
mergesort:
    mov     eax, [esp+8]
    sub     eax, [esp+4]
    cmp     eax, 0
    je      .end_sort
    cmp     eax, 2
    jl      .short_array
    sar     eax
    add     eax, [esp+4]
    push    [esp+16]
    push    [esp+16]
    push    eax
    push    [esp+16]
    call    mergesort
    add     esp, 4
    pop     eax
    push    [esp+16]
    push    eax
    call    mergesort
    pop     eax
    add     esp, 12
    mov     ecx, [esp+8]
    sub     ecx, [esp+4]
    sal     ecx, 2
    sub     esp, ecx
    sar     ecx, 2
    push    ecx
    mov     ecx, [esp+4*ecx+8]
    mov     edx, eax
    xor     esi, esi
    .beg_main_loop:
    cmp     ecx, eax
    je      .end_main_loop
    mov     edi, [esp]
    cmp     edx, [esp+4*edi+12]
    je      .end_main_loop
    push    eax
    mov     eax, [esp+4*edi+24]
    mov     edi, [eax+4*edx]
    mov     eax, [eax+4*ecx]
    cmp     eax, edi
    jle     .less_or_equal
    mov     [esp+4*esi+8], edi
    inc     edx
    jmp     .end_if
    .less_or_equal:
    mov     [esp+4*esi+8], eax
    inc     ecx
    .end_if:
    pop     eax
    inc     esi
    jmp     .beg_main_loop
    .end_main_loop:
    .beg_loop1:
    cmp     ecx, eax
    je      .end_loop1
    mov     edi, [esp]
    mov     edi, [esp+4*edi+20]
    mov     edi, [edi+4*ecx]
    mov     [esp+4*esi+4], edi
    inc     ecx
    inc     esi
    jmp     .beg_loop1
    .end_loop1:
    .beg_loop2:
    mov     edi, [esp]
    cmp     edx, [esp+4*edi+12]
    je      .end_loop2
    mov     edi, [esp+4*edi+20]
    mov     edi, [edi+4*edx]
    mov     [esp+4*esi+4], edi
    inc     edx
    inc     esi
    jmp     .beg_loop2
    .end_loop2:
    pop     eax
    mov     ecx, [esp+4*eax+4]
    mov     edx, ecx
    .copy_loop:
    cmp     ecx, [esp+4*eax+8]
    je      .copy_end
    sub     ecx, edx
    mov     edi, [esp+4*ecx]
    mov     esi, [esp+4*eax+16]
    add     ecx, edx
    mov     [esi+4*ecx], edi
    inc     ecx
    jmp     .copy_loop
    .copy_end:
    sal     eax, 2
    add     esp, eax
    .end_sort:
    ret
    .short_array:
    mov     eax, [esp+4]
    mov     ecx, [esp+12]
    mov     ecx, [ecx+4*eax]
    mov     edx, [esp+16]
    mov     [edx+4*eax], ecx
    ret
