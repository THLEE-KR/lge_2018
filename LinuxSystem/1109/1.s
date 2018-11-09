	.file	"1.c"
	.section	.rodata
.LC0:
	.string	"Hello, C: %d\n"
.LC2:
	.string	"%lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$42, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movabsq	$4614253070214989087, %rax
	movq	%rax, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	movl	$.LC2, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.6) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
