	.text
	.syntax unified
	.eabi_attribute	67, "2.09"	@ Tag_conformance
	.eabi_attribute	6, 1	@ Tag_CPU_arch
	.eabi_attribute	8, 1	@ Tag_ARM_ISA_use
	.eabi_attribute	34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute	17, 1	@ Tag_ABI_PCS_GOT_use
	.eabi_attribute	20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute	21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute	23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute	24, 1	@ Tag_ABI_align_needed
	.eabi_attribute	25, 1	@ Tag_ABI_align_preserved
	.eabi_attribute	38, 1	@ Tag_ABI_FP_16bit_format
	.eabi_attribute	14, 0	@ Tag_ABI_PCS_R9_use
	.file	"CoolLLVM"
	.globl	Object_init                     @ -- Begin function Object_init
	.p2align	2
	.type	Object_init,%function
	.code	32                              @ @Object_init
Object_init:
	.fnstart
@ %bb.0:                                @ %entry
	ldr	r1, .LCPI0_0
	mov	r2, #3
	mov	r3, #0
	str	r2, [r0, #4]
	str	r3, [r0]
	str	r1, [r0, #8]
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI0_0:
	.long	Object_dispTab
.Lfunc_end0:
	.size	Object_init, .Lfunc_end0-Object_init
	.fnend
                                        @ -- End function
	.globl	IO_init                         @ -- Begin function IO_init
	.p2align	2
	.type	IO_init,%function
	.code	32                              @ @IO_init
IO_init:
	.fnstart
@ %bb.0:                                @ %entry
	ldr	r1, .LCPI1_0
	mov	r2, #3
	mov	r3, #1
	str	r2, [r0, #4]
	str	r3, [r0]
	str	r1, [r0, #8]
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI1_0:
	.long	IO_dispTab
.Lfunc_end1:
	.size	IO_init, .Lfunc_end1-IO_init
	.fnend
                                        @ -- End function
	.globl	Main_init                       @ -- Begin function Main_init
	.p2align	2
	.type	Main_init,%function
	.code	32                              @ @Main_init
Main_init:
	.fnstart
@ %bb.0:                                @ %entry
	ldr	r1, .LCPI2_0
	mov	r2, #3
	mov	r3, #2
	str	r2, [r0, #4]
	str	r3, [r0]
	str	r1, [r0, #8]
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI2_0:
	.long	Main_dispTab
.Lfunc_end2:
	.size	Main_init, .Lfunc_end2-Main_init
	.fnend
                                        @ -- End function
	.globl	Int_init                        @ -- Begin function Int_init
	.p2align	2
	.type	Int_init,%function
	.code	32                              @ @Int_init
Int_init:
	.fnstart
@ %bb.0:                                @ %entry
	mov	r12, #0
	ldr	r2, .LCPI3_0
	mov	r1, #3
	mov	r3, #4
	stm	r0, {r1, r3}
	str	r2, [r0, #8]
	str	r12, [r0, #12]
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI3_0:
	.long	Int_dispTab
.Lfunc_end3:
	.size	Int_init, .Lfunc_end3-Int_init
	.fnend
                                        @ -- End function
	.globl	Bool_init                       @ -- Begin function Bool_init
	.p2align	2
	.type	Bool_init,%function
	.code	32                              @ @Bool_init
Bool_init:
	.fnstart
@ %bb.0:                                @ %entry
	mov	r1, #0
	mov	r2, #4
	strb	r1, [r0, #12]
	ldr	r1, .LCPI4_0
	str	r2, [r0]
	str	r2, [r0, #4]
	str	r1, [r0, #8]
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI4_0:
	.long	Bool_dispTab
.Lfunc_end4:
	.size	Bool_init, .Lfunc_end4-Bool_init
	.fnend
                                        @ -- End function
	.globl	String_init                     @ -- Begin function String_init
	.p2align	2
	.type	String_init,%function
	.code	32                              @ @String_init
String_init:
	.fnstart
@ %bb.0:                                @ %entry
	push	{r4, r5, r11, lr}
	mov	r4, r0
	ldr	r0, .LCPI5_0
	mov	r1, #5
	str	r0, [r4, #8]
	mov	r0, #20
	str	r1, [r4]
	str	r1, [r4, #4]
	bl	malloc
	mov	r5, r0
	bl	Int_init
	mov	r0, #0
	str	r0, [r5, #12]
	ldr	r0, .LCPI5_1
	str	r5, [r4, #12]
	str	r0, [r4, #16]
	pop	{r4, r5, r11, lr}
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI5_0:
	.long	String_dispTab
.LCPI5_1:
	.long	.LemptyStr
.Lfunc_end5:
	.size	String_init, .Lfunc_end5-String_init
	.fnend
                                        @ -- End function
	.globl	Object.abort                    @ -- Begin function Object.abort
	.p2align	2
	.type	Object.abort,%function
	.code	32                              @ @Object.abort
Object.abort:
	.fnstart
@ %bb.0:                                @ %entry
	push	{r4, lr}
	bl	Object.type_name
	ldr	r2, [r0, #16]
	ldr	r0, .LCPI6_0
	ldr	r1, .LCPI6_1
	bl	printf
	mov	r0, #1
	bl	exit
	mov	r0, #256
	bl	malloc
	mov	r4, r0
	bl	Object_init
	mov	r0, r4
	pop	{r4, lr}
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI6_0:
	.long	.Labort_format
.LCPI6_1:
	.long	.Labort_msg
.Lfunc_end6:
	.size	Object.abort, .Lfunc_end6-Object.abort
	.fnend
                                        @ -- End function
	.globl	Object.type_name                @ -- Begin function Object.type_name
	.p2align	2
	.type	Object.type_name,%function
	.code	32                              @ @Object.type_name
Object.type_name:
	.fnstart
@ %bb.0:                                @ %entry
	push	{r4, r5, r11, lr}
	ldr	r5, [r0]
	mov	r0, #32
	bl	malloc
	mov	r4, r0
	bl	String_init
	ldr	r0, .LCPI7_0
	ldr	r0, [r0, r5, lsl #2]
	str	r0, [r4, #16]
	bl	strlen
	ldr	r1, [r4, #12]
	str	r0, [r1, #12]
	mov	r0, r4
	pop	{r4, r5, r11, lr}
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI7_0:
	.long	.L.str_array
.Lfunc_end7:
	.size	Object.type_name, .Lfunc_end7-Object.type_name
	.fnend
                                        @ -- End function
	.globl	Object.copy                     @ -- Begin function Object.copy
	.p2align	2
	.type	Object.copy,%function
	.code	32                              @ @Object.copy
Object.copy:
	.fnstart
@ %bb.0:                                @ %entry
	push	{r4, r5, r11, lr}
	mov	r4, r0
	mov	r0, #256
	bl	malloc
	mov	r1, r4
	mov	r2, #256
	mov	r5, r0
	bl	memcpy
	mov	r0, r5
	pop	{r4, r5, r11, lr}
	mov	pc, lr
.Lfunc_end8:
	.size	Object.copy, .Lfunc_end8-Object.copy
	.fnend
                                        @ -- End function
	.globl	IO.out_string                   @ -- Begin function IO.out_string
	.p2align	2
	.type	IO.out_string,%function
	.code	32                              @ @IO.out_string
IO.out_string:
	.fnstart
@ %bb.0:                                @ %entry
	sub	sp, sp, #12
	push	{r4, lr}
	sub	sp, sp, #4
	mov	r4, r0
	add	r0, sp, #12
	stm	r0, {r1, r2, r3}
	ldr	r0, [sp, #28]
	bl	printf
	mov	r0, r4
	add	sp, sp, #4
	pop	{r4, lr}
	add	sp, sp, #12
	mov	pc, lr
.Lfunc_end9:
	.size	IO.out_string, .Lfunc_end9-IO.out_string
	.fnend
                                        @ -- End function
	.globl	IO.out_int                      @ -- Begin function IO.out_int
	.p2align	2
	.type	IO.out_int,%function
	.code	32                              @ @IO.out_int
IO.out_int:
	.fnstart
@ %bb.0:                                @ %entry
	sub	sp, sp, #12
	push	{r4, lr}
	sub	sp, sp, #4
	mov	r4, r0
	add	r0, sp, #12
	stm	r0, {r1, r2, r3}
	ldr	r1, [sp, #24]
	ldr	r0, .LCPI10_0
	bl	printf
	mov	r0, r4
	add	sp, sp, #4
	pop	{r4, lr}
	add	sp, sp, #12
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI10_0:
	.long	.Lformat_int
.Lfunc_end10:
	.size	IO.out_int, .Lfunc_end10-IO.out_int
	.fnend
                                        @ -- End function
	.globl	IO.in_string                    @ -- Begin function IO.in_string
	.p2align	2
	.type	IO.in_string,%function
	.code	32                              @ @IO.in_string
IO.in_string:
	.fnstart
@ %bb.0:                                @ %entry
	push	{r4, r5, r6, lr}
	sub	sp, sp, #8
	sub	sp, sp, #1024
	mov	r0, #32
	bl	malloc
	mov	r4, r0
	bl	String_init
	ldr	r0, .LCPI11_0
	add	r1, sp, #6
	str	r1, [r4, #16]
	bl	scanf
	ldr	r0, [r4, #16]
	bl	strlen
	ldr	r1, [r4, #12]
	str	r0, [r1, #12]
	mov	r0, r4
	add	sp, sp, #8
	add	sp, sp, #1024
	pop	{r4, r5, r6, lr}
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI11_0:
	.long	.Lformat_string
.Lfunc_end11:
	.size	IO.in_string, .Lfunc_end11-IO.in_string
	.fnend
                                        @ -- End function
	.globl	IO.in_int                       @ -- Begin function IO.in_int
	.p2align	2
	.type	IO.in_int,%function
	.code	32                              @ @IO.in_int
IO.in_int:
	.fnstart
@ %bb.0:                                @ %entry
	push	{r4, lr}
	mov	r0, #20
	bl	malloc
	mov	r4, r0
	bl	Int_init
	mov	r0, #0
	mov	r1, r4
	str	r0, [r1, #12]!
	ldr	r0, .LCPI12_0
	bl	scanf
	mov	r0, r4
	pop	{r4, lr}
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI12_0:
	.long	.Lformat_int
.Lfunc_end12:
	.size	IO.in_int, .Lfunc_end12-IO.in_int
	.fnend
                                        @ -- End function


	.globl	Main.main                       @ -- Begin function Main.main
	.p2align	2
	.type	Main.main,%function
	.code	32                              @ @Main.main
Main.main:
	.fnstart
@ %bb.0:                                @ %entry
	push	{r4, r5, r6, lr}
	sub	sp, sp, #8
	cmp	r0, #0
	beq	.LBB13_2
@ %bb.1:                                @ %notVoidBlock
	mov	r4, r0
	ldr	r0, [r0, #8]
	ldr	r6, [r0, #16]
	mov	r0, #20
	bl	malloc
	mov	r5, r0
	bl	Int_init
	mov	r0, #1
	str	r0, [r5, #12]
	mov	r0, #20
	bl	malloc
	mov	r5, r0
	bl	Int_init
	mov	r0, #2
	str	r0, [r5, #12]
	mov	r0, #20
	bl	malloc
	mov	r5, r0
	bl	Int_init
	mov	r0, #3
	mov	r1, r5
	str	r0, [r1, #12]!
	ldr	r0, [r1], #4
	mov	r1, sp
	str	r0, [r1], #4
	mov	r0, r4
	ldm	r5, {r1, r2, r3}
	mov	lr, pc
	mov	pc, r6
	b	.LBB13_3
.LBB13_2:                               @ %isVoidBlock1
	ldr	r0, .LCPI13_0
	ldr	r1, .LCPI13_1
	ldr	r2, .LCPI13_2
	ldr	r3, .LCPI13_3
	bl	printf
	mov	r0, #1
	bl	exit
	mov	r0, #0
.LBB13_3:                               @ %isVoidBlock1
	add	sp, sp, #8
	pop	{r4, r5, r6, lr}
	mov	pc, lr
	.p2align	2
@ %bb.4:
.LCPI13_0:
	.long	.L__unnamed_1
.LCPI13_1:
	.long	.Lfile_name
.LCPI13_2:
	.long	.L__unnamed_2
.LCPI13_3:
	.long	.L_dispatch_msg
.Lfunc_end13:
	.size	Main.main, .Lfunc_end13-Main.main
	.fnend
                                        @ -- End function




										
	.globl	main                            @ -- Begin function main
	.p2align	2
	.type	main,%function
	.code	32                              @ @main
main:
	.fnstart
@ %bb.0:                                @ %entry
	push	{r4, lr}
	mov	r0, #256
	bl	malloc
	mov	r4, r0
	bl	Main_init
	mov	r0, r4
	bl	Main.main
	ldr	r0, .LCPI14_0
	bl	printf
	pop	{r4, lr}
	mov	pc, lr
	.p2align	2
@ %bb.1:
.LCPI14_0:
	.long	.L__unnamed_3
.Lfunc_end14:
	.size	main, .Lfunc_end14-main
	.fnend
                                        @ -- End function
	.globl	String.length                   @ -- Begin function String.length
	.p2align	2
	.type	String.length,%function
	.code	32                              @ @String.length
String.length:
	.fnstart
@ %bb.0:                                @ %entry
	ldr	r0, [r0, #12]
	mov	pc, lr
.Lfunc_end15:
	.size	String.length, .Lfunc_end15-String.length
	.fnend
                                        @ -- End function
	.globl	String.concat                   @ -- Begin function String.concat
	.p2align	2
	.type	String.concat,%function
	.code	32                              @ @String.concat
String.concat:
	.fnstart
@ %bb.0:                                @ %entry
	sub	sp, sp, #12
	push	{r4, r5, r6, r7, r8, lr}
	sub	sp, sp, #4
	mov	r5, r0
	add	r0, sp, #28
	stm	r0, {r1, r2, r3}
	ldr	r0, [sp, #40]
	ldr	r6, [r0, #12]
	ldr	r0, [r5, #12]
	ldr	r7, [r0, #12]
	add	r8, r7, r6
	mov	r0, r8
	bl	malloc
	ldr	r1, [r5, #16]
	mov	r2, r7
	mov	r4, r0
	bl	memcpy
	ldr	r1, [sp, #44]
	add	r0, r4, r7
	mov	r2, r6
	bl	memcpy
	mov	r0, #32
	bl	malloc
	mov	r5, r0
	bl	String_init
	ldr	r0, [r5, #12]
	str	r4, [r5, #16]
	str	r8, [r0, #12]
	mov	r0, r5
	add	sp, sp, #4
	pop	{r4, r5, r6, r7, r8, lr}
	add	sp, sp, #12
	mov	pc, lr
.Lfunc_end16:
	.size	String.concat, .Lfunc_end16-String.concat
	.fnend
                                        @ -- End function
	.globl	String.substr                   @ -- Begin function String.substr
	.p2align	2
	.type	String.substr,%function
	.code	32                              @ @String.substr
String.substr:
	.fnstart
@ %bb.0:                                @ %entry
	sub	sp, sp, #12
	push	{r4, r5, r6, lr}
	sub	sp, sp, #4
	ldr	r5, [sp, #48]
	mov	r4, r0
	add	r0, sp, #20
	stm	r0, {r1, r2, r3}
	mov	r0, r5
	bl	malloc
	mov	r6, r0
	ldr	r0, [r4, #16]
	ldr	r1, [sp, #32]
	mov	r2, r5
	add	r1, r0, r1
	mov	r0, r6
	bl	memcpy
	mov	r0, #32
	bl	malloc
	mov	r4, r0
	bl	String_init
	ldr	r0, [r4, #12]
	str	r6, [r4, #16]
	str	r5, [r0, #12]
	mov	r0, r4
	add	sp, sp, #4
	pop	{r4, r5, r6, lr}
	add	sp, sp, #12
	mov	pc, lr
.Lfunc_end17:
	.size	String.substr, .Lfunc_end17-String.substr
	.fnend
                                        @ -- End function
	.type	.LObject,%object                @ @Object
	.section	.rodata.str1.1,"aMS",%progbits,1
.LObject:
	.asciz	"Object"
	.size	.LObject, 7

	.type	.LIO,%object                    @ @IO
.LIO:
	.asciz	"IO"
	.size	.LIO, 3

	.type	.LInt,%object                   @ @Int
.LInt:
	.asciz	"Int"
	.size	.LInt, 4

	.type	.LBool,%object                  @ @Bool
.LBool:
	.asciz	"Bool"
	.size	.LBool, 5

	.type	.LString,%object                @ @String
.LString:
	.asciz	"String"
	.size	.LString, 7

	.type	.LMain,%object                  @ @Main
.LMain:
	.asciz	"Main"
	.size	.LMain, 5

	.type	.L.str_array,%object            @ @.str_array
	.section	.rodata,"a",%progbits
	.p2align	4
.L.str_array:
	.long	.LObject
	.long	.LIO
	.long	.LMain
	.long	.LInt
	.long	.LBool
	.long	.LString
	.size	.L.str_array, 24

	.type	.Lfile_name,%object             @ @file_name
	.section	.rodata.str1.1,"aMS",%progbits,1
.Lfile_name:
	.asciz	"./llvm/hello_world.cl"
	.size	.Lfile_name, 22

	.type	.L_dispatch_msg,%object         @ @_dispatch_msg
.L_dispatch_msg:
	.asciz	": Dispatch to void.\n"
	.size	.L_dispatch_msg, 21

	.type	.L_case_abort,%object           @ @_case_abort
.L_case_abort:
	.asciz	"No match in case statement for Class "
	.size	.L_case_abort, 38

	.type	.L_case_abort2,%object          @ @_case_abort2
.L_case_abort2:
	.asciz	"Match on void in case statement.\n"
	.size	.L_case_abort2, 34

	.type	.L__unnamed_3,%object           @ @0
.L__unnamed_3:
	.asciz	"COOL program successfully executed\n"
	.size	.L__unnamed_3, 36

	.type	Object_dispTab,%object          @ @Object_dispTab
	.section	.rodata,"a",%progbits
	.globl	Object_dispTab
	.p2align	2
Object_dispTab:
	.long	Object.abort
	.long	Object.type_name
	.long	Object.copy
	.size	Object_dispTab, 12

	.type	IO_dispTab,%object              @ @IO_dispTab
	.globl	IO_dispTab
	.p2align	4
IO_dispTab:
	.long	Object.abort
	.long	Object.type_name
	.long	Object.copy
	.long	IO.out_string
	.long	IO.out_int
	.long	IO.in_string
	.long	IO.in_int
	.size	IO_dispTab, 28

	.type	Main_dispTab,%object            @ @Main_dispTab
	.globl	Main_dispTab
	.p2align	4
Main_dispTab:
	.long	Object.abort
	.long	Object.type_name
	.long	Object.copy
	.long	IO.out_string
	.long	IO.out_int
	.long	IO.in_string
	.long	IO.in_int
	.long	Main.main
	.size	Main_dispTab, 32

	.type	Int_dispTab,%object             @ @Int_dispTab
	.globl	Int_dispTab
	.p2align	2
Int_dispTab:
	.long	Object.abort
	.long	Object.type_name
	.long	Object.copy
	.size	Int_dispTab, 12

	.type	Bool_dispTab,%object            @ @Bool_dispTab
	.globl	Bool_dispTab
	.p2align	2
Bool_dispTab:
	.long	Object.abort
	.long	Object.type_name
	.long	Object.copy
	.size	Bool_dispTab, 12

	.type	String_dispTab,%object          @ @String_dispTab
	.globl	String_dispTab
	.p2align	4
String_dispTab:
	.long	Object.abort
	.long	Object.type_name
	.long	Object.copy
	.long	String.length
	.long	String.concat
	.long	String.substr
	.size	String_dispTab, 24

	.type	.LemptyStr,%object              @ @emptyStr
	.section	.rodata.str1.1,"aMS",%progbits,1
.LemptyStr:
	.zero	1
	.size	.LemptyStr, 1

	.type	.Labort_format,%object          @ @abort_format
.Labort_format:
	.asciz	"%s %s\n"
	.size	.Labort_format, 7

	.type	.Labort_msg,%object             @ @abort_msg
.Labort_msg:
	.asciz	"Abort called from class"
	.size	.Labort_msg, 24

	.type	.Lformat_int,%object            @ @format_int
.Lformat_int:
	.asciz	"%d"
	.size	.Lformat_int, 3

	.type	.Lformat_string,%object         @ @format_string
.Lformat_string:
	.asciz	"%s"
	.size	.Lformat_string, 3

	.type	.L__unnamed_1,%object           @ @1
.L__unnamed_1:
	.asciz	"%s%s%s"
	.size	.L__unnamed_1, 7

	.type	.L__unnamed_2,%object           @ @2
.L__unnamed_2:
	.asciz	":1"
	.size	.L__unnamed_2, 3

	.section	".note.GNU-stack","",%progbits
