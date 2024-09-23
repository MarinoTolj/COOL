	.text
	.file	"CoolLLVM"
	.globl	Object_init                     # -- Begin function Object_init
	.p2align	4, 0x90
	.type	Object_init,@function
Object_init:                            # @Object_init
	.cfi_startproc
# %bb.0:                                # %entry
	movabsq	$12884901888, %rax              # imm = 0x300000000
	movq	%rax, (%rdi)
	movq	Object_dispTab@GOTPCREL(%rip), %rax
	movq	%rax, 8(%rdi)
	retq
.Lfunc_end0:
	.size	Object_init, .Lfunc_end0-Object_init
	.cfi_endproc
                                        # -- End function
	.globl	IO_init                         # -- Begin function IO_init
	.p2align	4, 0x90
	.type	IO_init,@function
IO_init:                                # @IO_init
	.cfi_startproc
# %bb.0:                                # %entry
	movabsq	$12884901889, %rax              # imm = 0x300000001
	movq	%rax, (%rdi)
	movq	IO_dispTab@GOTPCREL(%rip), %rax
	movq	%rax, 8(%rdi)
	retq
.Lfunc_end1:
	.size	IO_init, .Lfunc_end1-IO_init
	.cfi_endproc
                                        # -- End function
	.globl	Main_init                       # -- Begin function Main_init
	.p2align	4, 0x90
	.type	Main_init,@function
Main_init:                              # @Main_init
	.cfi_startproc
# %bb.0:                                # %entry
	movabsq	$12884901890, %rax              # imm = 0x300000002
	movq	%rax, (%rdi)
	movq	Main_dispTab@GOTPCREL(%rip), %rax
	movq	%rax, 8(%rdi)
	retq
.Lfunc_end2:
	.size	Main_init, .Lfunc_end2-Main_init
	.cfi_endproc
                                        # -- End function
	.globl	Int_init                        # -- Begin function Int_init
	.p2align	4, 0x90
	.type	Int_init,@function
Int_init:                               # @Int_init
	.cfi_startproc
# %bb.0:                                # %entry
	movabsq	$17179869187, %rax              # imm = 0x400000003
	movq	%rax, (%rdi)
	movq	Int_dispTab@GOTPCREL(%rip), %rax
	movq	%rax, 8(%rdi)
	movl	$0, 16(%rdi)
	retq
.Lfunc_end3:
	.size	Int_init, .Lfunc_end3-Int_init
	.cfi_endproc
                                        # -- End function
	.globl	Bool_init                       # -- Begin function Bool_init
	.p2align	4, 0x90
	.type	Bool_init,@function
Bool_init:                              # @Bool_init
	.cfi_startproc
# %bb.0:                                # %entry
	movabsq	$17179869188, %rax              # imm = 0x400000004
	movq	%rax, (%rdi)
	movq	Bool_dispTab@GOTPCREL(%rip), %rax
	movq	%rax, 8(%rdi)
	movb	$0, 16(%rdi)
	retq
.Lfunc_end4:
	.size	Bool_init, .Lfunc_end4-Bool_init
	.cfi_endproc
                                        # -- End function
	.globl	String_init                     # -- Begin function String_init
	.p2align	4, 0x90
	.type	String_init,@function
String_init:                            # @String_init
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movq	%rdi, %r14
	movabsq	$21474836485, %rax              # imm = 0x500000005
	movq	%rax, (%rdi)
	movq	String_dispTab@GOTPCREL(%rip), %rax
	movq	%rax, 8(%rdi)
	movl	$20, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	Int_init@PLT
	movl	$0, 16(%rbx)
	movq	%rbx, 16(%r14)
	movq	$.LemptyStr, 24(%r14)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end5:
	.size	String_init, .Lfunc_end5-String_init
	.cfi_endproc
                                        # -- End function
	.globl	Object.abort                    # -- Begin function Object.abort
	.p2align	4, 0x90
	.type	Object.abort,@function
Object.abort:                           # @Object.abort
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	callq	Object.type_name@PLT
	movq	24(%rax), %rdx
	movl	$.Labort_format, %edi
	movl	$.Labort_msg, %esi
	xorl	%eax, %eax
	callq	printf@PLT
	movl	$1, %edi
	callq	exit@PLT
	movl	$256, %edi                      # imm = 0x100
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	Object_init@PLT
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end6:
	.size	Object.abort, .Lfunc_end6-Object.abort
	.cfi_endproc
                                        # -- End function
	.globl	Object.type_name                # -- Begin function Object.type_name
	.p2align	4, 0x90
	.type	Object.type_name,@function
Object.type_name:                       # @Object.type_name
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movslq	(%rdi), %rax
	movq	.L.str_array(,%rax,8), %r14
	movl	$32, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	String_init@PLT
	movq	%r14, 24(%rbx)
	movq	%r14, %rdi
	callq	strlen@PLT
	movq	16(%rbx), %rcx
	movl	%eax, 16(%rcx)
	movq	%rbx, %rax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end7:
	.size	Object.type_name, .Lfunc_end7-Object.type_name
	.cfi_endproc
                                        # -- End function
	.globl	Object.copy                     # -- Begin function Object.copy
	.p2align	4, 0x90
	.type	Object.copy,@function
Object.copy:                            # @Object.copy
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movq	%rdi, %r14
	movl	$256, %edi                      # imm = 0x100
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	movq	%r14, %rsi
	movl	$256, %edx                      # imm = 0x100
	callq	memcpy@PLT
	movq	%rbx, %rax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end8:
	.size	Object.copy, .Lfunc_end8-Object.copy
	.cfi_endproc
                                        # -- End function
	.globl	IO.out_string                   # -- Begin function IO.out_string
	.p2align	4, 0x90
	.type	IO.out_string,@function
IO.out_string:                          # @IO.out_string
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movq	%rdi, %rbx
	movq	40(%rsp), %rdi
	xorl	%eax, %eax
	callq	printf@PLT
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end9:
	.size	IO.out_string, .Lfunc_end9-IO.out_string
	.cfi_endproc
                                        # -- End function
	.globl	IO.out_int                      # -- Begin function IO.out_int
	.p2align	4, 0x90
	.type	IO.out_int,@function
IO.out_int:                             # @IO.out_int
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movq	%rdi, %rbx
	movl	32(%rsp), %esi
	movl	$.Lformat_int, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end10:
	.size	IO.out_int, .Lfunc_end10-IO.out_int
	.cfi_endproc
                                        # -- End function
	.globl	IO.in_string                    # -- Begin function IO.in_string
	.p2align	4, 0x90
	.type	IO.in_string,@function
IO.in_string:                           # @IO.in_string
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$1040, %rsp                     # imm = 0x410
	.cfi_def_cfa_offset 1056
	.cfi_offset %rbx, -16
	movl	$32, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	String_init@PLT
	leaq	14(%rsp), %rsi
	movq	%rsi, 24(%rbx)
	movl	$.Lformat_string, %edi
	xorl	%eax, %eax
	callq	scanf@PLT
	movq	24(%rbx), %rdi
	callq	strlen@PLT
	movq	16(%rbx), %rcx
	movl	%eax, 16(%rcx)
	movq	%rbx, %rax
	addq	$1040, %rsp                     # imm = 0x410
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end11:
	.size	IO.in_string, .Lfunc_end11-IO.in_string
	.cfi_endproc
                                        # -- End function
	.globl	IO.in_int                       # -- Begin function IO.in_int
	.p2align	4, 0x90
	.type	IO.in_int,@function
IO.in_int:                              # @IO.in_int
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movl	$20, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	Int_init@PLT
	leaq	16(%rbx), %rsi
	movl	$0, 16(%rbx)
	movl	$.Lformat_int, %edi
	xorl	%eax, %eax
	callq	scanf@PLT
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end12:
	.size	IO.in_int, .Lfunc_end12-IO.in_int
	.cfi_endproc
                                        # -- End function


	.globl	Main.main                       # -- Begin function Main.main
	.p2align	4, 0x90
	.type	Main.main,@function
Main.main:                              # @Main.main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%r15
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	.cfi_offset %r15, -16
	testq	%rdi, %rdi
	je	.LBB13_1
# %bb.3:                                # %notVoidBlock
	movq	%rdi, %r14
	movq	8(%rdi), %rax
	movq	32(%rax), %r15
	movl	$20, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	Int_init@PLT
	movl	$1, 16(%rbx)
	movl	$20, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	Int_init@PLT
	movl	$2, 16(%rbx)
	movl	$20, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	Int_init@PLT
	movl	$3, 16(%rbx)
	subq	$8, %rsp
	.cfi_adjust_cfa_offset 8
	movq	16(%rbx), %rax
	movq	(%rbx), %rcx
	movq	8(%rbx), %rdx
	movq	%r14, %rdi
	pushq	%rax
	.cfi_adjust_cfa_offset 8
	pushq	%rdx
	.cfi_adjust_cfa_offset 8
	pushq	%rcx
	.cfi_adjust_cfa_offset 8
	callq	*%r15
	addq	$32, %rsp
	.cfi_adjust_cfa_offset -32
	jmp	.LBB13_2
.LBB13_1:                               # %isVoidBlock1
	movl	$.L__unnamed_1, %edi
	movl	$.Lfile_name, %esi
	movl	$.L__unnamed_2, %edx
	movl	$.L_dispatch_msg, %ecx
	xorl	%eax, %eax
	callq	printf@PLT
	movl	$1, %edi
	callq	exit@PLT
	xorl	%eax, %eax
.LBB13_2:                               # %isVoidBlock1
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end13:
	.size	Main.main, .Lfunc_end13-Main.main
	.cfi_endproc
                                        # -- End function




	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function


main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movl	$256, %edi                      # imm = 0x100
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	Main_init@PLT
	movq	%rbx, %rdi
	callq	Main.main@PLT
	movl	$.L__unnamed_3, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end14:
	.size	main, .Lfunc_end14-main
	.cfi_endproc
                                        # -- End function
	.globl	String.length                   # -- Begin function String.length
	.p2align	4, 0x90
	.type	String.length,@function
String.length:                          # @String.length
	.cfi_startproc
# %bb.0:                                # %entry
	movq	16(%rdi), %rax
	retq
.Lfunc_end15:
	.size	String.length, .Lfunc_end15-String.length
	.cfi_endproc
                                        # -- End function
	.globl	String.concat                   # -- Begin function String.concat
	.p2align	4, 0x90
	.type	String.concat,@function
String.concat:                          # @String.concat
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%r12
	.cfi_def_cfa_offset 40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -48
	.cfi_offset %r12, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	%rdi, %rbx
	movq	16(%rdi), %rax
	movslq	16(%rax), %rbp
	movq	64(%rsp), %rax
	movl	16(%rax), %r15d
	leal	(%rbp,%r15), %r14d
	movl	%r14d, %edi
	callq	malloc@PLT
	movq	%rax, %r12
	movq	24(%rbx), %rsi
	movq	%rax, %rdi
	movl	%ebp, %edx
	callq	memcpy@PLT
	addq	%r12, %rbp
	movq	72(%rsp), %rsi
	movq	%rbp, %rdi
	movl	%r15d, %edx
	callq	memcpy@PLT
	movl	$32, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	String_init@PLT
	movq	%r12, 24(%rbx)
	movq	16(%rbx), %rax
	movl	%r14d, 16(%rax)
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end16:
	.size	String.concat, .Lfunc_end16-String.concat
	.cfi_endproc
                                        # -- End function
	.globl	String.substr                   # -- Begin function String.substr
	.p2align	4, 0x90
	.type	String.substr,@function
String.substr:                          # @String.substr
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	pushq	%rax
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	%rdi, %r14
	movl	88(%rsp), %ebp
	movl	%ebp, %edi
	callq	malloc@PLT
	movq	%rax, %r15
	movslq	64(%rsp), %rsi
	addq	24(%r14), %rsi
	movq	%rax, %rdi
	movl	%ebp, %edx
	callq	memcpy@PLT
	movl	$32, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	callq	String_init@PLT
	movq	%r15, 24(%rbx)
	movq	16(%rbx), %rax
	movl	%ebp, 16(%rax)
	movq	%rbx, %rax
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end17:
	.size	String.substr, .Lfunc_end17-String.substr
	.cfi_endproc
                                        # -- End function
	.type	.LObject,@object                # @Object
	.section	.rodata.str1.1,"aMS",@progbits,1
.LObject:
	.asciz	"Object"
	.size	.LObject, 7

	.type	.LIO,@object                    # @IO
.LIO:
	.asciz	"IO"
	.size	.LIO, 3

	.type	.LInt,@object                   # @Int
.LInt:
	.asciz	"Int"
	.size	.LInt, 4

	.type	.LBool,@object                  # @Bool
.LBool:
	.asciz	"Bool"
	.size	.LBool, 5

	.type	.LString,@object                # @String
.LString:
	.asciz	"String"
	.size	.LString, 7

	.type	.LMain,@object                  # @Main
.LMain:
	.asciz	"Main"
	.size	.LMain, 5

	.type	.L.str_array,@object            # @.str_array
	.section	.rodata,"a",@progbits
	.p2align	4
.L.str_array:
	.quad	.LObject
	.quad	.LIO
	.quad	.LMain
	.quad	.LInt
	.quad	.LBool
	.quad	.LString
	.size	.L.str_array, 48

	.type	.Lfile_name,@object             # @file_name
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lfile_name:
	.asciz	"./llvm/hello_world.cl"
	.size	.Lfile_name, 22

	.type	.L_dispatch_msg,@object         # @_dispatch_msg
.L_dispatch_msg:
	.asciz	": Dispatch to void.\n"
	.size	.L_dispatch_msg, 21

	.type	.L_case_abort,@object           # @_case_abort
.L_case_abort:
	.asciz	"No match in case statement for Class "
	.size	.L_case_abort, 38

	.type	.L_case_abort2,@object          # @_case_abort2
.L_case_abort2:
	.asciz	"Match on void in case statement.\n"
	.size	.L_case_abort2, 34

	.type	.L__unnamed_3,@object           # @0
.L__unnamed_3:
	.asciz	"COOL program successfully executed\n"
	.size	.L__unnamed_3, 36

	.type	Object_dispTab,@object          # @Object_dispTab
	.section	.rodata,"a",@progbits
	.globl	Object_dispTab
	.p2align	4
Object_dispTab:
	.quad	Object.abort
	.quad	Object.type_name
	.quad	Object.copy
	.size	Object_dispTab, 24

	.type	IO_dispTab,@object              # @IO_dispTab
	.globl	IO_dispTab
	.p2align	4
IO_dispTab:
	.quad	Object.abort
	.quad	Object.type_name
	.quad	Object.copy
	.quad	IO.out_string
	.quad	IO.out_int
	.quad	IO.in_string
	.quad	IO.in_int
	.size	IO_dispTab, 56

	.type	Main_dispTab,@object            # @Main_dispTab
	.globl	Main_dispTab
	.p2align	4
Main_dispTab:
	.quad	Object.abort
	.quad	Object.type_name
	.quad	Object.copy
	.quad	IO.out_string
	.quad	IO.out_int
	.quad	IO.in_string
	.quad	IO.in_int
	.quad	Main.main
	.size	Main_dispTab, 64

	.type	Int_dispTab,@object             # @Int_dispTab
	.globl	Int_dispTab
	.p2align	4
Int_dispTab:
	.quad	Object.abort
	.quad	Object.type_name
	.quad	Object.copy
	.size	Int_dispTab, 24

	.type	Bool_dispTab,@object            # @Bool_dispTab
	.globl	Bool_dispTab
	.p2align	4
Bool_dispTab:
	.quad	Object.abort
	.quad	Object.type_name
	.quad	Object.copy
	.size	Bool_dispTab, 24

	.type	String_dispTab,@object          # @String_dispTab
	.globl	String_dispTab
	.p2align	4
String_dispTab:
	.quad	Object.abort
	.quad	Object.type_name
	.quad	Object.copy
	.quad	String.length
	.quad	String.concat
	.quad	String.substr
	.size	String_dispTab, 48

	.type	.LemptyStr,@object              # @emptyStr
	.section	.rodata.str1.1,"aMS",@progbits,1
.LemptyStr:
	.zero	1
	.size	.LemptyStr, 1

	.type	.Labort_format,@object          # @abort_format
.Labort_format:
	.asciz	"%s %s\n"
	.size	.Labort_format, 7

	.type	.Labort_msg,@object             # @abort_msg
.Labort_msg:
	.asciz	"Abort called from class"
	.size	.Labort_msg, 24

	.type	.Lformat_int,@object            # @format_int
.Lformat_int:
	.asciz	"%d"
	.size	.Lformat_int, 3

	.type	.Lformat_string,@object         # @format_string
.Lformat_string:
	.asciz	"%s"
	.size	.Lformat_string, 3

	.type	.L__unnamed_1,@object           # @1
.L__unnamed_1:
	.asciz	"%s%s%s"
	.size	.L__unnamed_1, 7

	.type	.L__unnamed_2,@object           # @2
.L__unnamed_2:
	.asciz	":1"
	.size	.L__unnamed_2, 3

	.section	".note.GNU-stack","",@progbits
