	.text
	.p2align 4
	.globl _secure_zero
_secure_zero:
LFB4:
	testq	%rsi, %rsi
	je	L1
	addq	%rdi, %rsi
	.p2align 4,,10
	.p2align 3
L3:
	movq	%rdi, %rax
	addq	$1, %rdi
	cmpq	%rdi, %rsi
	movb	$0, (%rax)
	jne	L3
L1:
	ret
LFE4:
	.section __TEXT,__text_startup,regular,pure_instructions
	.p2align 4
	.globl _main
_main:
LFB5:
	pushq	%rbx
LCFI0:
	movl	$10, %edi
	subq	$16, %rsp
LCFI1:
	call	_malloc
	movq	%rax, %rbx
	movq	%rax, %rdi
	call	_free
	movb	$0, (%rbx)
	xorl	%eax, %eax
	movb	$0, 1(%rbx)
	movb	$0, 2(%rbx)
	movb	$0, 3(%rbx)
	movb	$0, 4(%rbx)
	movb	$0, 5(%rbx)
	movb	$0, 6(%rbx)
	movb	$0, 7(%rbx)
	movb	$0, 8(%rbx)
	movb	$0, 9(%rbx)
	movb	$0, 6(%rsp)
	movb	$0, 7(%rsp)
	movb	$0, 8(%rsp)
	movb	$0, 9(%rsp)
	movb	$0, 10(%rsp)
	movb	$0, 11(%rsp)
	movb	$0, 12(%rsp)
	movb	$0, 13(%rsp)
	movb	$0, 14(%rsp)
	movb	$0, 15(%rsp)
	addq	$16, %rsp
LCFI2:
	popq	%rbx
LCFI3:
	ret
LFE5:
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
	.quad	LFB4-.
	.set L$set$2,LFE4-LFB4
	.quad L$set$2
	.uleb128 0
	.align 3
LEFDE1:
LSFDE3:
	.set L$set$3,LEFDE3-LASFDE3
	.long L$set$3
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB5-.
	.set L$set$4,LFE5-LFB5
	.quad L$set$4
	.uleb128 0
	.byte	0x4
	.set L$set$5,LCFI0-LFB5
	.long L$set$5
	.byte	0xe
	.uleb128 0x10
	.byte	0x83
	.uleb128 0x2
	.byte	0x4
	.set L$set$6,LCFI1-LCFI0
	.long L$set$6
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.set L$set$7,LCFI2-LCFI1
	.long L$set$7
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.set L$set$8,LCFI3-LCFI2
	.long L$set$8
	.byte	0xe
	.uleb128 0x8
	.align 3
LEFDE3:
	.ident	"GCC: (Homebrew GCC 13.2.0) 13.2.0"
	.subsections_via_symbols
