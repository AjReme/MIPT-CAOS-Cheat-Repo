    .intel_syntax noprefix
    .text
    .global calc, vector_sum
calc:
    addsd       xmm0, xmm1
    cvtsi2sd    xmm3, edi
    addsd       xmm2, xmm3
    divsd       xmm0, xmm2
    ret
vector_sum:
    xor         rax, rax
.beg_loop:
    cmp         rax, rdi
    je          .end_loop
    movaps      xmm0, [rsi+4*rax]
    movaps      xmm1, [rdx+4*rax]
    addps       xmm0, xmm1
    movaps      [rcx+4*rax], xmm0
    add         rax, 4
    jmp         .beg_loop
.end_loop:
    ret
