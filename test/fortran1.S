	.text
	.cstring
lC0:
	.ascii "fortran1.f90\0"
	.const
lC1:
	.ascii "Matrix size = "
	.align 2
lC2:
	.long	1000
	.text
_MAIN__:
LFB0:
	pushq	%rbp
LCFI0:
	movq	%rsp, %rbp
LCFI1:
	subq	$544, %rsp
	leaq	lC0(%rip), %rax
	movq	%rax, -536(%rbp)
	movl	$8, -528(%rbp)
	movl	$128, -544(%rbp)
	movl	$6, -540(%rbp)
	leaq	-544(%rbp), %rax
	movq	%rax, %rdi
	call	__gfortran_st_write
	leaq	-544(%rbp), %rax
	movl	$14, %edx
	leaq	lC1(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	__gfortran_transfer_character_write
	leaq	-544(%rbp), %rax
	movl	$4, %edx
	leaq	lC2(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	__gfortran_transfer_integer_write
	leaq	-544(%rbp), %rax
	movq	%rax, %rdi
	call	__gfortran_st_write_done
	movl	$1, -4(%rbp)
L5:
	cmpl	$1000, -4(%rbp)
	setg	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	jne	L6
	movl	$1, -8(%rbp)
L4:
	cmpl	$1000, -8(%rbp)
	setg	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	jne	L7
	movl	-8(%rbp), %eax
	cltq
	imulq	$1000, %rax, %rdx
	movl	-4(%rbp), %eax
	cltq
	addq	%rdx, %rax
	subq	$1001, %rax
	leaq	0(,%rax,8), %rdx
	leaq	_a.3(%rip), %rax
	movsd	lC3(%rip), %xmm0
	movsd	%xmm0, (%rdx,%rax)
	movl	-8(%rbp), %eax
	cltq
	imulq	$1000, %rax, %rdx
	movl	-4(%rbp), %eax
	cltq
	addq	%rdx, %rax
	subq	$1001, %rax
	leaq	0(,%rax,8), %rdx
	leaq	_b.2(%rip), %rax
	movsd	lC4(%rip), %xmm0
	movsd	%xmm0, (%rdx,%rax)
	movl	-8(%rbp), %eax
	cltq
	imulq	$1000, %rax, %rdx
	movl	-4(%rbp), %eax
	cltq
	addq	%rdx, %rax
	subq	$1001, %rax
	leaq	0(,%rax,8), %rdx
	leaq	_c.1(%rip), %rax
	pxor	%xmm0, %xmm0
	movsd	%xmm0, (%rdx,%rax)
	addl	$1, -8(%rbp)
	jmp	L4
L7:
	nop
	addl	$1, -4(%rbp)
	jmp	L5
L6:
	nop
	nop
	leave
LCFI2:
	ret
LFE0:
	.globl _main
_main:
LFB1:
	pushq	%rbp
LCFI3:
	movq	%rsp, %rbp
LCFI4:
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	__gfortran_set_args
	leaq	_options.1.0(%rip), %rax
	movq	%rax, %rsi
	movl	$7, %edi
	call	__gfortran_set_options
	call	_MAIN__
	movl	$0, %eax
	leave
LCFI5:
	ret
LFE1:
	.zerofill __DATA,__bss,_a.3,8000000,5
	.zerofill __DATA,__bss,_b.2,8000000,5
	.zerofill __DATA,__bss,_c.1,8000000,5
	.const
	.align 4
_options.1.0:
	.long	2116
	.long	4095
	.long	0
	.long	1
	.long	1
	.long	0
	.long	31
	.literal8
	.align 3
lC3:
	.long	0
	.long	1072693248
	.align 3
lC4:
	.long	0
	.long	1073741824
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x1
	.byte	0x10
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 3
LECIE1:
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB0-.
	.set L$set$2,LFE0-LFB0
	.quad L$set$2
	.uleb128 0
	.byte	0x4
	.set L$set$3,LCFI0-LFB0
	.long L$set$3
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.set L$set$4,LCFI1-LCFI0
	.long L$set$4
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.set L$set$5,LCFI2-LCFI1
	.long L$set$5
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 3
LEFDE1:
LSFDE3:
	.set L$set$6,LEFDE3-LASFDE3
	.long L$set$6
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB1-.
	.set L$set$7,LFE1-LFB1
	.quad L$set$7
	.uleb128 0
	.byte	0x4
	.set L$set$8,LCFI3-LFB1
	.long L$set$8
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.set L$set$9,LCFI4-LCFI3
	.long L$set$9
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.set L$set$10,LCFI5-LCFI4
	.long L$set$10
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.align 3
LEFDE3:
	.ident	"GCC: (Homebrew GCC 13.2.0) 13.2.0"
	.subsections_via_symbols
