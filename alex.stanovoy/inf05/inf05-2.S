    .intel_syntax noprefix
    .text
    .global dot_product
dot_product:
    xor     rax, rax
    xorps   xmm0, xmm0
    mov     rcx, rdi
    sar     rcx, 2
    sal     rcx, 2
    .beg_loop1:
    cmp     rax, rcx
    je      .end_loop1
    movups  xmm1, [rsi+4*rax]
    movups  xmm2, [rdx+4*rax]
    mulps   xmm1, xmm2
    haddps  xmm1, xmm1
    haddps  xmm1, xmm1
    addss   xmm0, xmm1
    add     rax, 4
    jmp     .beg_loop1
    .end_loop1:
    .beg_loop2:
    cmp     rax, rdi
    je      .end_loop2
    movups  xmm1, [rsi+4*rax]
    movups  xmm2, [rdx+4*rax]
    mulps   xmm1, xmm2
    addss   xmm0, xmm1
    inc     rax
    jmp     .beg_loop2
    .end_loop2:
    ret
