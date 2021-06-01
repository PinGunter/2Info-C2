	.file	"daxpy.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Error en la llamda. Hace falta el par\303\241metro N (tama\303\261o de vector)"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC3:
	.string	"Tiempo: %11.9f\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB20:
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
	jne	.L14
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movslq	%eax, %rdx
	leaq	15(,%rdx,8), %rdx
	shrq	$4, %rdx
	salq	$4, %rdx
	subq	%rdx, %rsp
	movq	%rsp, %r12
	subq	%rdx, %rsp
	movq	%rsp, %r14
	testl	%eax, %eax
	jle	.L3
	leal	-1(%rax), %r13d
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L4:
	xorl	%edi, %edi
	call	time
	movq	%rax, %rdi
	call	srand48
	call	drand48
	xorl	%edi, %edi
	movsd	%xmm0, (%r12,%rbx,8)
	call	time
	movq	%rax, %rdi
	call	srand48
	call	drand48
	movq	%rbx, %rax
	movsd	%xmm0, (%r14,%rbx,8)
	addq	$1, %rbx
	cmpq	%r13, %rax
	jne	.L4
	leaq	-64(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movsd	.LC1(%rip), %xmm1
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L6:
	movsd	(%r12,%rax,8), %xmm0
	movq	%rax, %rdx
	mulsd	%xmm1, %xmm0
	addsd	(%r14,%rax,8), %xmm0
	movsd	%xmm0, (%r14,%rax,8)
	addq	$1, %rax
	cmpq	%r13, %rdx
	jne	.L6
.L7:
	leaq	-48(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	-40(%rbp), %rax
	pxor	%xmm0, %xmm0
	subq	-56(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	movq	-48(%rbp), %rax
	subq	-64(%rbp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$.LC3, %edi
	movl	$1, %eax
	divsd	.LC2(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	printf
	leaq	-32(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L3:
	.cfi_restore_state
	leaq	-64(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	jmp	.L7
.L14:
	movl	$.LC0, %edi
	call	puts
	movl	$1, %edi
	call	exit
	.cfi_endproc
.LFE20:
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
