	.file	"daxpy.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Error en la llamda. Hace falta el par\303\241metro N (tama\303\261o de vector)"
.LC3:
	.string	"Tiempo: %11.9f\n"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	cmpl	$2, %edi
	je	.L2
	movl	$.LC0, %edi
	call	puts
	movl	$1, %edi
	call	exit
.L2:
	movq	8(%rsi), %rdi
	xorl	%r12d, %r12d
	call	atoi
	movl	%eax, %ebx
	cltq
	leaq	15(,%rax,8), %rax
	shrq	$4, %rax
	salq	$4, %rax
	subq	%rax, %rsp
	movq	%rsp, %r13
	subq	%rax, %rsp
	movq	%rsp, %r14
.L3:
	cmpl	%r12d, %ebx
	jle	.L9
	xorl	%edi, %edi
	call	time
	movq	%rax, %rdi
	call	srand48
	call	drand48
	xorl	%edi, %edi
	movsd	%xmm0, 0(%r13,%r12,8)
	call	time
	movq	%rax, %rdi
	call	srand48
	call	drand48
	movsd	%xmm0, (%r14,%r12,8)
	incq	%r12
	jmp	.L3
.L9:
	leaq	-64(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movsd	.LC1(%rip), %xmm1
	xorl	%eax, %eax
.L5:
	cmpl	%eax, %ebx
	jle	.L10
	movsd	0(%r13,%rax,8), %xmm0
	mulsd	%xmm1, %xmm0
	addsd	(%r14,%rax,8), %xmm0
	movsd	%xmm0, (%r14,%rax,8)
	incq	%rax
	jmp	.L5
.L10:
	leaq	-48(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	-40(%rbp), %rax
	subq	-56(%rbp), %rax
	movl	$.LC3, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	-48(%rbp), %rax
	subq	-64(%rbp), %rax
	divsd	.LC2(%rip), %xmm0
	cvtsi2sdq	%rax, %xmm1
	movb	$1, %al
	addsd	%xmm1, %xmm0
	call	printf
	leaq	-32(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	1030792151
	.long	1076549386
	.align 8
.LC2:
	.long	0
	.long	1104006501
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
