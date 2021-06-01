	.file	"daxpy.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Error en la llamda. Hace falta el par\303\241metro N (tama\303\261o de vector)"
.LC3:
	.string	"Tiempo: %11.9f\n"
	.text
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
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%edi, -148(%rbp)
	movq	%rsi, -160(%rbp)
	movq	%rsp, %rax
	movq	%rax, %rbx
	cmpl	$2, -148(%rbp)
	je	.L2
	movl	$.LC0, %edi
	call	puts
	movl	$1, %edi
	call	exit
.L2:
	movq	-160(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, -52(%rbp)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -72(%rbp)
	movl	-52(%rbp), %eax
	cltq
	subq	$1, %rax
	movq	%rax, -80(%rbp)
	movl	-52(%rbp), %eax
	cltq
	movq	%rax, -176(%rbp)
	movq	$0, -168(%rbp)
	movl	-52(%rbp), %eax
	cltq
	movq	%rax, -192(%rbp)
	movq	$0, -184(%rbp)
	movl	-52(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %esi
	movl	$0, %edx
	divq	%rsi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$7, %rax
	shrq	$3, %rax
	salq	$3, %rax
	movq	%rax, -88(%rbp)
	movl	-52(%rbp), %eax
	cltq
	subq	$1, %rax
	movq	%rax, -96(%rbp)
	movl	-52(%rbp), %eax
	cltq
	movq	%rax, %r14
	movl	$0, %r15d
	movl	-52(%rbp), %eax
	cltq
	movq	%rax, %r12
	movl	$0, %r13d
	movl	-52(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %esi
	movl	$0, %edx
	divq	%rsi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$7, %rax
	shrq	$3, %rax
	salq	$3, %rax
	movq	%rax, -104(%rbp)
	movl	$0, -60(%rbp)
	jmp	.L3
.L4:
	movl	$0, %edi
	call	time
	movq	%rax, %rdi
	call	srand48
	call	drand48
	movq	%xmm0, %rax
	movq	-88(%rbp), %rdx
	movl	-60(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	%rax, (%rdx,%rcx,8)
	movl	$0, %edi
	call	time
	movq	%rax, %rdi
	call	srand48
	call	drand48
	movq	%xmm0, %rax
	movq	-104(%rbp), %rdx
	movl	-60(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	%rax, (%rdx,%rcx,8)
	addl	$1, -60(%rbp)
.L3:
	movl	-60(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L4
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime
	movl	$0, -56(%rbp)
	jmp	.L5
.L6:
	movq	-88(%rbp), %rax
	movl	-56(%rbp), %edx
	movslq	%edx, %rdx
	movsd	(%rax,%rdx,8), %xmm0
	movapd	%xmm0, %xmm1
	mulsd	-72(%rbp), %xmm1
	movq	-104(%rbp), %rax
	movl	-56(%rbp), %edx
	movslq	%edx, %rdx
	movsd	(%rax,%rdx,8), %xmm0
	addsd	%xmm1, %xmm0
	movq	-104(%rbp), %rax
	movl	-56(%rbp), %edx
	movslq	%edx, %rdx
	movsd	%xmm0, (%rax,%rdx,8)
	addl	$1, -56(%rbp)
.L5:
	movl	-56(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L6
	leaq	-144(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime
	movq	-144(%rbp), %rdx
	movq	-128(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm1
	movq	-136(%rbp), %rdx
	movq	-120(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC2(%rip), %xmm2
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -112(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %xmm0
	movl	$.LC3, %edi
	movl	$1, %eax
	call	printf
	movq	%rbx, %rsp
	movl	$0, %eax
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata
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
