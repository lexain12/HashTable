global findElementByValue

findElementByValue:
 	mov    rax,QWORD [rdi]
 	mov    rdi,QWORD [rdi+0x8]
 	mov    rax,QWORD [rax+0x10]
 	sub    rdi,0x1

 	je      .end
 	movdqa xmm1,OWORD [rsi]
 	xor    edx,edx

    .loop:
        mov    rax,QWORD [rax+0x10]
        movdqa xmm0,xmm1
        mov    rcx,QWORD [rax]
        pcmpeqd xmm0,OWORD [rcx]
        pmovmskb ecx,xmm0
        cmp    ecx,0xffff
        je     .end1

        add    rdx,0x1
        cmp    rdx,rdi
        jne    .loop
.end:
 	xor    eax,eax
.end1:
 	ret

