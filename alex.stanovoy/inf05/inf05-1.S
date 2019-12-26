    .intel_syntax noprefix
    .text
    .global my_sin
my_sin:
    mov         rax, 1
    movapd      xmm2, xmm0
    movapd      xmm1, xmm0
    mulsd       xmm1, xmm0
    .beg_loop:
    mulsd       xmm2, xmm1
    inc         rax
    cvtsi2sd    xmm3, rax
    divsd       xmm2, xmm3
    inc         rax
    cvtsi2sd    xmm3, rax
    divsd       xmm2, xmm3
    mov         rsi, -1
    cvtsi2sd    xmm3, rsi
    mulsd       xmm2, xmm3
    mov         rsi, 0
    cvtsi2sd    xmm3, rsi
    comisd      xmm2, xmm3
    je          .end_loop
    addsd       xmm0, xmm2
    jmp         .beg_loop
    .end_loop:
    ret
