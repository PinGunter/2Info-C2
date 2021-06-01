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
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	cmpl	$2, %edi
	jne	.L15
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movq	%rax, %r12
	cltq
	leaq	15(,%rax,8), %rax
	shrq	$4, %rax
	salq	$4, %rax
	subq	%rax, %rsp
	movq	%rsp, %r13
	subq	%rax, %rsp
	movq	%rsp, %r15
	testl	%r12d, %r12d
	jle	.L3
	leal	-1(%r12), %r14d
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
	movsd	%xmm0, 0(%r13,%rbx,8)
	call	time
	movq	%rax, %rdi
	call	srand48
	call	drand48
	movq	%rbx, %rax
	movsd	%xmm0, (%r15,%rbx,8)
	addq	$1, %rbx
	cmpq	%r14, %rax
	jne	.L4
	xorl	%edi, %edi
	leaq	-80(%rbp), %rsi
	call	clock_gettime
	cmpl	$1, %r12d
	je	.L8
	shrl	%r12d
	movapd	.LC1(%rip), %xmm1
	xorl	%edx, %edx
	salq	$4, %r12
	.p2align 4,,10
	.p2align 3
.L6:
	movupd	0(%r13,%rdx), %xmm0
	movupd	(%r15,%rdx), %xmm2
	mulpd	%xmm1, %xmm0
	addpd	%xmm2, %xmm0
	movups	%xmm0, (%r15,%rdx)
	addq	$16, %rdx
	cmpq	%rdx, %r12
	jne	.L6
.L8:
	leaq	-64(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	-56(%rbp), %rax
	pxor	%xmm0, %xmm0
	subq	-72(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	movq	-64(%rbp), %rax
	subq	-80(%rbp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$.LC3, %edi
	movl	$1, %eax
	divsd	.LC2(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	printf
	leaq	-40(%rbp), %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L3:
	.cfi_restore_state
	leaq	-80(%rbp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	jmp	.L8
.L15:
	movl	$.LC0, %edi
	call	puts
	movl	$1, %edi
	call	exit
	.cfi_endproc
.LFE20:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC1:
	.long	1030792151
	.long	1076549386
	.long	1030792151
	.long	1076549386
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	0
	.long	1104006501
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
