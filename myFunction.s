global findElementByValue

findElementByValue:
 	mov    rax,QWORD [rdi]
 	mov    r8,QWORD [rdi+0x8]
 	mov    rax,QWORD [rax+0x10]
 	sub    r8,0x1
 	je     .end
 	movq   xmm1,QWORD [rsi]
 	xor    edx,edx

    .loop:
        mov    rax,QWORD [rax+0x10]
        mov    rcx,QWORD [rax]
        movq   xmm0,QWORD [rcx]
        pcmpeqd xmm0,xmm1
        pmovmskb ecx,xmm0
        cmp    ecx,0xffff
        je     .end
        add    rdx,0x1
        cmp    rdx,r8
        jne    .loop

 	sub    r8,0x2
 	cmp    r8,rdx
 	mov    edx,0x0
 	cmove  rax,rdx

.end:
 	ret

