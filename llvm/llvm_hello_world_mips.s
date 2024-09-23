	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.text
	.file	"CoolLLVM"
	.globl	Object_init                     # -- Begin function Object_init
	.p2align	2
	.type	Object_init,@function
	.set	nomicromips
	.set	nomips16
	.ent	Object_init
Object_init:                            # @Object_init
	.cfi_startproc
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$1, $zero, 3
	sw	$1, 4($4)
	lui	$1, %hi(Object_dispTab)
	addiu	$1, $1, %lo(Object_dispTab)
	sw	$1, 8($4)
	jr	$ra
	sw	$zero, 0($4)
	.set	at
	.set	macro
	.set	reorder
	.end	Object_init
$func_end0:
	.size	Object_init, ($func_end0)-Object_init
	.cfi_endproc
                                        # -- End function
	.globl	IO_init                         # -- Begin function IO_init
	.p2align	2
	.type	IO_init,@function
	.set	nomicromips
	.set	nomips16
	.ent	IO_init
IO_init:                                # @IO_init
	.cfi_startproc
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$1, $zero, 3
	sw	$1, 4($4)
	addiu	$1, $zero, 1
	sw	$1, 0($4)
	lui	$1, %hi(IO_dispTab)
	addiu	$1, $1, %lo(IO_dispTab)
	jr	$ra
	sw	$1, 8($4)
	.set	at
	.set	macro
	.set	reorder
	.end	IO_init
$func_end1:
	.size	IO_init, ($func_end1)-IO_init
	.cfi_endproc
                                        # -- End function
	.globl	Main_init                       # -- Begin function Main_init
	.p2align	2
	.type	Main_init,@function
	.set	nomicromips
	.set	nomips16
	.ent	Main_init
Main_init:                              # @Main_init
	.cfi_startproc
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$1, $zero, 3
	sw	$1, 4($4)
	addiu	$1, $zero, 2
	sw	$1, 0($4)
	lui	$1, %hi(Main_dispTab)
	addiu	$1, $1, %lo(Main_dispTab)
	jr	$ra
	sw	$1, 8($4)
	.set	at
	.set	macro
	.set	reorder
	.end	Main_init
$func_end2:
	.size	Main_init, ($func_end2)-Main_init
	.cfi_endproc
                                        # -- End function
	.globl	Int_init                        # -- Begin function Int_init
	.p2align	2
	.type	Int_init,@function
	.set	nomicromips
	.set	nomips16
	.ent	Int_init
Int_init:                               # @Int_init
	.cfi_startproc
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$1, $zero, 4
	sw	$1, 4($4)
	addiu	$1, $zero, 3
	sw	$1, 0($4)
	lui	$1, %hi(Int_dispTab)
	addiu	$1, $1, %lo(Int_dispTab)
	sw	$1, 8($4)
	jr	$ra
	sw	$zero, 12($4)
	.set	at
	.set	macro
	.set	reorder
	.end	Int_init
$func_end3:
	.size	Int_init, ($func_end3)-Int_init
	.cfi_endproc
                                        # -- End function
	.globl	Bool_init                       # -- Begin function Bool_init
	.p2align	2
	.type	Bool_init,@function
	.set	nomicromips
	.set	nomips16
	.ent	Bool_init
Bool_init:                              # @Bool_init
	.cfi_startproc
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	sb	$zero, 12($4)
	addiu	$1, $zero, 4
	sw	$1, 4($4)
	sw	$1, 0($4)
	lui	$1, %hi(Bool_dispTab)
	addiu	$1, $1, %lo(Bool_dispTab)
	jr	$ra
	sw	$1, 8($4)
	.set	at
	.set	macro
	.set	reorder
	.end	Bool_init
$func_end4:
	.size	Bool_init, ($func_end4)-Bool_init
	.cfi_endproc
                                        # -- End function
	.globl	String_init                     # -- Begin function String_init
	.p2align	2
	.type	String_init,@function
	.set	nomicromips
	.set	nomips16
	.ent	String_init
String_init:                            # @String_init
	.cfi_startproc
	.frame	$sp,32,$ra
	.mask 	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -32
	.cfi_def_cfa_offset 32
	sw	$ra, 28($sp)                    # 4-byte Folded Spill
	sw	$17, 24($sp)                    # 4-byte Folded Spill
	sw	$16, 20($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 17, -8
	.cfi_offset 16, -12
	move	$16, $4
	addiu	$1, $zero, 5
	sw	$1, 4($4)
	sw	$1, 0($4)
	lui	$1, %hi(String_dispTab)
	addiu	$1, $1, %lo(String_dispTab)
	sw	$1, 8($4)
	jal	malloc
	addiu	$4, $zero, 20
	move	$17, $2
	jal	Int_init
	move	$4, $2
	lui	$1, %hi($emptyStr)
	sw	$zero, 12($17)
	addiu	$1, $1, %lo($emptyStr)
	sw	$1, 16($16)
	sw	$17, 12($16)
	lw	$16, 20($sp)                    # 4-byte Folded Reload
	lw	$17, 24($sp)                    # 4-byte Folded Reload
	lw	$ra, 28($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 32
	.set	at
	.set	macro
	.set	reorder
	.end	String_init
$func_end5:
	.size	String_init, ($func_end5)-String_init
	.cfi_endproc
                                        # -- End function
	.globl	Object.abort                    # -- Begin function Object.abort
	.p2align	2
	.type	Object.abort,@function
	.set	nomicromips
	.set	nomips16
	.ent	Object.abort
Object.abort:                           # @Object.abort
	.cfi_startproc
	.frame	$sp,24,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -24
	.cfi_def_cfa_offset 24
	sw	$ra, 20($sp)                    # 4-byte Folded Spill
	sw	$16, 16($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 16, -8
	jal	Object.type_name
	nop
	lw	$6, 16($2)
	lui	$1, %hi($abort_format)
	addiu	$4, $1, %lo($abort_format)
	lui	$1, %hi($abort_msg)
	jal	printf
	addiu	$5, $1, %lo($abort_msg)
	jal	exit
	addiu	$4, $zero, 1
	jal	malloc
	addiu	$4, $zero, 256
	move	$16, $2
	jal	Object_init
	move	$4, $2
	move	$2, $16
	lw	$16, 16($sp)                    # 4-byte Folded Reload
	lw	$ra, 20($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	Object.abort
$func_end6:
	.size	Object.abort, ($func_end6)-Object.abort
	.cfi_endproc
                                        # -- End function
	.globl	Object.type_name                # -- Begin function Object.type_name
	.p2align	2
	.type	Object.type_name,@function
	.set	nomicromips
	.set	nomips16
	.ent	Object.type_name
Object.type_name:                       # @Object.type_name
	.cfi_startproc
	.frame	$sp,32,$ra
	.mask 	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -32
	.cfi_def_cfa_offset 32
	sw	$ra, 28($sp)                    # 4-byte Folded Spill
	sw	$17, 24($sp)                    # 4-byte Folded Spill
	sw	$16, 20($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 17, -8
	.cfi_offset 16, -12
	lw	$17, 0($4)
	jal	malloc
	addiu	$4, $zero, 32
	move	$16, $2
	jal	String_init
	move	$4, $2
	lui	$1, %hi($.str_array)
	addiu	$1, $1, %lo($.str_array)
	sll	$2, $17, 2
	addu	$1, $1, $2
	lw	$4, 0($1)
	jal	strlen
	sw	$4, 16($16)
	lw	$1, 12($16)
	sw	$2, 12($1)
	move	$2, $16
	lw	$16, 20($sp)                    # 4-byte Folded Reload
	lw	$17, 24($sp)                    # 4-byte Folded Reload
	lw	$ra, 28($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 32
	.set	at
	.set	macro
	.set	reorder
	.end	Object.type_name
$func_end7:
	.size	Object.type_name, ($func_end7)-Object.type_name
	.cfi_endproc
                                        # -- End function
	.globl	Object.copy                     # -- Begin function Object.copy
	.p2align	2
	.type	Object.copy,@function
	.set	nomicromips
	.set	nomips16
	.ent	Object.copy
Object.copy:                            # @Object.copy
	.cfi_startproc
	.frame	$sp,32,$ra
	.mask 	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -32
	.cfi_def_cfa_offset 32
	sw	$ra, 28($sp)                    # 4-byte Folded Spill
	sw	$17, 24($sp)                    # 4-byte Folded Spill
	sw	$16, 20($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 17, -8
	.cfi_offset 16, -12
	move	$16, $4
	jal	malloc
	addiu	$4, $zero, 256
	move	$17, $2
	move	$4, $2
	move	$5, $16
	jal	memcpy
	addiu	$6, $zero, 256
	move	$2, $17
	lw	$16, 20($sp)                    # 4-byte Folded Reload
	lw	$17, 24($sp)                    # 4-byte Folded Reload
	lw	$ra, 28($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 32
	.set	at
	.set	macro
	.set	reorder
	.end	Object.copy
$func_end8:
	.size	Object.copy, ($func_end8)-Object.copy
	.cfi_endproc
                                        # -- End function
	.globl	IO.out_string                   # -- Begin function IO.out_string
	.p2align	2
	.type	IO.out_string,@function
	.set	nomicromips
	.set	nomips16
	.ent	IO.out_string
IO.out_string:                          # @IO.out_string
	.cfi_startproc
	.frame	$sp,24,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -24
	.cfi_def_cfa_offset 24
	sw	$ra, 20($sp)                    # 4-byte Folded Spill
	sw	$16, 16($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 16, -8
	move	$16, $4
	lw	$4, 44($sp)
	jal	printf
	nop
	move	$2, $16
	lw	$16, 16($sp)                    # 4-byte Folded Reload
	lw	$ra, 20($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	IO.out_string
$func_end9:
	.size	IO.out_string, ($func_end9)-IO.out_string
	.cfi_endproc
                                        # -- End function
	.globl	IO.out_int                      # -- Begin function IO.out_int
	.p2align	2
	.type	IO.out_int,@function
	.set	nomicromips
	.set	nomips16
	.ent	IO.out_int
IO.out_int:                             # @IO.out_int
	.cfi_startproc
	.frame	$sp,24,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -24
	.cfi_def_cfa_offset 24
	sw	$ra, 20($sp)                    # 4-byte Folded Spill
	sw	$16, 16($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 16, -8
	move	$16, $4
	lw	$5, 40($sp)
	lui	$1, %hi($format_int)
	jal	printf
	addiu	$4, $1, %lo($format_int)
	move	$2, $16
	lw	$16, 16($sp)                    # 4-byte Folded Reload
	lw	$ra, 20($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	IO.out_int
$func_end10:
	.size	IO.out_int, ($func_end10)-IO.out_int
	.cfi_endproc
                                        # -- End function
	.globl	IO.in_string                    # -- Begin function IO.in_string
	.p2align	2
	.type	IO.in_string,@function
	.set	nomicromips
	.set	nomips16
	.ent	IO.in_string
IO.in_string:                           # @IO.in_string
	.cfi_startproc
	.frame	$sp,1056,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -1056
	.cfi_def_cfa_offset 1056
	sw	$ra, 1052($sp)                  # 4-byte Folded Spill
	sw	$16, 1048($sp)                  # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 16, -8
	jal	malloc
	addiu	$4, $zero, 32
	move	$16, $2
	jal	String_init
	move	$4, $2
	addiu	$5, $sp, 20
	sw	$5, 16($16)
	lui	$1, %hi($format_string)
	jal	scanf
	addiu	$4, $1, %lo($format_string)
	lw	$4, 16($16)
	jal	strlen
	nop
	lw	$1, 12($16)
	sw	$2, 12($1)
	move	$2, $16
	lw	$16, 1048($sp)                  # 4-byte Folded Reload
	lw	$ra, 1052($sp)                  # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 1056
	.set	at
	.set	macro
	.set	reorder
	.end	IO.in_string
$func_end11:
	.size	IO.in_string, ($func_end11)-IO.in_string
	.cfi_endproc
                                        # -- End function
	.globl	IO.in_int                       # -- Begin function IO.in_int
	.p2align	2
	.type	IO.in_int,@function
	.set	nomicromips
	.set	nomips16
	.ent	IO.in_int
IO.in_int:                              # @IO.in_int
	.cfi_startproc
	.frame	$sp,24,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -24
	.cfi_def_cfa_offset 24
	sw	$ra, 20($sp)                    # 4-byte Folded Spill
	sw	$16, 16($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 16, -8
	jal	malloc
	addiu	$4, $zero, 20
	move	$16, $2
	jal	Int_init
	move	$4, $2
	sw	$zero, 12($16)
	lui	$1, %hi($format_int)
	addiu	$4, $1, %lo($format_int)
	jal	scanf
	addiu	$5, $16, 12
	move	$2, $16
	lw	$16, 16($sp)                    # 4-byte Folded Reload
	lw	$ra, 20($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	IO.in_int
$func_end12:
	.size	IO.in_int, ($func_end12)-IO.in_int
	.cfi_endproc
                                        # -- End function
	.globl	Main.main                       # -- Begin function Main.main
	.p2align	2
	.type	Main.main,@function
	.set	nomicromips
	.set	nomips16
	.ent	Main.main
Main.main:                              # @Main.main
	.cfi_startproc
	.frame	$sp,40,$ra
	.mask 	0x80070000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -40
	.cfi_def_cfa_offset 40
	sw	$ra, 36($sp)                    # 4-byte Folded Spill
	sw	$18, 32($sp)                    # 4-byte Folded Spill
	sw	$17, 28($sp)                    # 4-byte Folded Spill
	sw	$16, 24($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 18, -8
	.cfi_offset 17, -12
	.cfi_offset 16, -16
	beqz	$4, $BB13_2
	nop
# %bb.1:                                # %notVoidBlock
	move	$16, $4
	lw	$1, 8($4)
	lw	$17, 16($1)
	jal	malloc
	addiu	$4, $zero, 20
	move	$18, $2
	jal	Int_init
	move	$4, $2
	addiu	$1, $zero, 2
	sw	$1, 12($18)
	lw	$5, 0($18)
	lw	$6, 4($18)
	lw	$7, 8($18)
	sw	$1, 16($sp)
	move	$25, $17
	jalr	$25
	move	$4, $16
	lw	$16, 24($sp)                    # 4-byte Folded Reload
	lw	$17, 28($sp)                    # 4-byte Folded Reload
	lw	$18, 32($sp)                    # 4-byte Folded Reload
	lw	$ra, 36($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 40
$BB13_2:                                # %isVoidBlock1
	lui	$1, %hi($__unnamed_1)
	addiu	$4, $1, %lo($__unnamed_1)
	lui	$1, %hi($file_name)
	addiu	$5, $1, %lo($file_name)
	lui	$1, %hi($__unnamed_2)
	addiu	$6, $1, %lo($__unnamed_2)
	lui	$1, %hi($_dispatch_msg)
	jal	printf
	addiu	$7, $1, %lo($_dispatch_msg)
	jal	exit
	addiu	$4, $zero, 1
	addiu	$2, $zero, 0
	lw	$16, 24($sp)                    # 4-byte Folded Reload
	lw	$17, 28($sp)                    # 4-byte Folded Reload
	lw	$18, 32($sp)                    # 4-byte Folded Reload
	lw	$ra, 36($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 40
	.set	at
	.set	macro
	.set	reorder
	.end	Main.main
$func_end13:
	.size	Main.main, ($func_end13)-Main.main
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.ent	main
main:                                   # @main
	.cfi_startproc
	.frame	$sp,24,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -24
	.cfi_def_cfa_offset 24
	sw	$ra, 20($sp)                    # 4-byte Folded Spill
	sw	$16, 16($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 16, -8
	jal	malloc
	addiu	$4, $zero, 256
	move	$16, $2
	jal	Main_init
	move	$4, $2
	jal	Main.main
	move	$4, $16
	lui	$1, %hi($__unnamed_3)
	jal	printf
	addiu	$4, $1, %lo($__unnamed_3)
	lw	$16, 16($sp)                    # 4-byte Folded Reload
	lw	$ra, 20($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end14:
	.size	main, ($func_end14)-main
	.cfi_endproc
                                        # -- End function
	.globl	String.length                   # -- Begin function String.length
	.p2align	2
	.type	String.length,@function
	.set	nomicromips
	.set	nomips16
	.ent	String.length
String.length:                          # @String.length
	.cfi_startproc
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	lw	$2, 12($4)
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	String.length
$func_end15:
	.size	String.length, ($func_end15)-String.length
	.cfi_endproc
                                        # -- End function
	.globl	String.concat                   # -- Begin function String.concat
	.p2align	2
	.type	String.concat,@function
	.set	nomicromips
	.set	nomips16
	.ent	String.concat
String.concat:                          # @String.concat
	.cfi_startproc
	.frame	$sp,48,$ra
	.mask 	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -48
	.cfi_def_cfa_offset 48
	sw	$ra, 44($sp)                    # 4-byte Folded Spill
	sw	$21, 40($sp)                    # 4-byte Folded Spill
	sw	$20, 36($sp)                    # 4-byte Folded Spill
	sw	$19, 32($sp)                    # 4-byte Folded Spill
	sw	$18, 28($sp)                    # 4-byte Folded Spill
	sw	$17, 24($sp)                    # 4-byte Folded Spill
	sw	$16, 20($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 21, -8
	.cfi_offset 20, -12
	.cfi_offset 19, -16
	.cfi_offset 18, -20
	.cfi_offset 17, -24
	.cfi_offset 16, -28
	move	$16, $4
	lw	$1, 64($sp)
	lw	$17, 12($1)
	lw	$1, 12($4)
	lw	$18, 12($1)
	addu	$19, $18, $17
	lw	$20, 68($sp)
	jal	malloc
	move	$4, $19
	move	$21, $2
	lw	$5, 16($16)
	move	$4, $2
	jal	memcpy
	move	$6, $18
	addu	$4, $21, $18
	move	$5, $20
	jal	memcpy
	move	$6, $17
	jal	malloc
	addiu	$4, $zero, 32
	move	$16, $2
	jal	String_init
	move	$4, $2
	sw	$21, 16($16)
	lw	$1, 12($16)
	sw	$19, 12($1)
	move	$2, $16
	lw	$16, 20($sp)                    # 4-byte Folded Reload
	lw	$17, 24($sp)                    # 4-byte Folded Reload
	lw	$18, 28($sp)                    # 4-byte Folded Reload
	lw	$19, 32($sp)                    # 4-byte Folded Reload
	lw	$20, 36($sp)                    # 4-byte Folded Reload
	lw	$21, 40($sp)                    # 4-byte Folded Reload
	lw	$ra, 44($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 48
	.set	at
	.set	macro
	.set	reorder
	.end	String.concat
$func_end16:
	.size	String.concat, ($func_end16)-String.concat
	.cfi_endproc
                                        # -- End function
	.globl	String.substr                   # -- Begin function String.substr
	.p2align	2
	.type	String.substr,@function
	.set	nomicromips
	.set	nomips16
	.ent	String.substr
String.substr:                          # @String.substr
	.cfi_startproc
	.frame	$sp,40,$ra
	.mask 	0x800f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -40
	.cfi_def_cfa_offset 40
	sw	$ra, 36($sp)                    # 4-byte Folded Spill
	sw	$19, 32($sp)                    # 4-byte Folded Spill
	sw	$18, 28($sp)                    # 4-byte Folded Spill
	sw	$17, 24($sp)                    # 4-byte Folded Spill
	sw	$16, 20($sp)                    # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 19, -8
	.cfi_offset 18, -12
	.cfi_offset 17, -16
	.cfi_offset 16, -20
	move	$16, $4
	lw	$19, 56($sp)
	lw	$17, 72($sp)
	jal	malloc
	move	$4, $17
	move	$18, $2
	lw	$1, 16($16)
	addu	$5, $1, $19
	move	$4, $2
	jal	memcpy
	move	$6, $17
	jal	malloc
	addiu	$4, $zero, 32
	move	$16, $2
	jal	String_init
	move	$4, $2
	sw	$18, 16($16)
	lw	$1, 12($16)
	sw	$17, 12($1)
	move	$2, $16
	lw	$16, 20($sp)                    # 4-byte Folded Reload
	lw	$17, 24($sp)                    # 4-byte Folded Reload
	lw	$18, 28($sp)                    # 4-byte Folded Reload
	lw	$19, 32($sp)                    # 4-byte Folded Reload
	lw	$ra, 36($sp)                    # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 40
	.set	at
	.set	macro
	.set	reorder
	.end	String.substr
$func_end17:
	.size	String.substr, ($func_end17)-String.substr
	.cfi_endproc
                                        # -- End function
	.type	$Object,@object                 # @Object
	.section	.rodata.str1.1,"aMS",@progbits,1
$Object:
	.asciz	"Object"
	.size	$Object, 7

	.type	$IO,@object                     # @IO
$IO:
	.asciz	"IO"
	.size	$IO, 3

	.type	$Int,@object                    # @Int
$Int:
	.asciz	"Int"
	.size	$Int, 4

	.type	$Bool,@object                   # @Bool
$Bool:
	.asciz	"Bool"
	.size	$Bool, 5

	.type	$String,@object                 # @String
$String:
	.asciz	"String"
	.size	$String, 7

	.type	$Main,@object                   # @Main
$Main:
	.asciz	"Main"
	.size	$Main, 5

	.type	$.str_array,@object             # @.str_array
	.section	.rodata,"a",@progbits
	.p2align	4
$.str_array:
	.4byte	($Object)
	.4byte	($IO)
	.4byte	($Main)
	.4byte	($Int)
	.4byte	($Bool)
	.4byte	($String)
	.size	$.str_array, 24

	.type	$file_name,@object              # @file_name
	.section	.rodata.str1.1,"aMS",@progbits,1
$file_name:
	.asciz	"./llvm/hello_world.cl"
	.size	$file_name, 22

	.type	$_dispatch_msg,@object          # @_dispatch_msg
$_dispatch_msg:
	.asciz	": Dispatch to void.\n"
	.size	$_dispatch_msg, 21

	.type	$_case_abort,@object            # @_case_abort
$_case_abort:
	.asciz	"No match in case statement for Class "
	.size	$_case_abort, 38

	.type	$_case_abort2,@object           # @_case_abort2
$_case_abort2:
	.asciz	"Match on void in case statement.\n"
	.size	$_case_abort2, 34

	.type	$__unnamed_3,@object            # @0
$__unnamed_3:
	.asciz	"COOL program successfully executed\n"
	.size	$__unnamed_3, 36

	.type	Object_dispTab,@object          # @Object_dispTab
	.section	.rodata,"a",@progbits
	.globl	Object_dispTab
	.p2align	3
Object_dispTab:
	.4byte	Object.abort
	.4byte	Object.type_name
	.4byte	Object.copy
	.size	Object_dispTab, 12

	.type	IO_dispTab,@object              # @IO_dispTab
	.globl	IO_dispTab
	.p2align	4
IO_dispTab:
	.4byte	Object.abort
	.4byte	Object.type_name
	.4byte	Object.copy
	.4byte	IO.out_string
	.4byte	IO.out_int
	.4byte	IO.in_string
	.4byte	IO.in_int
	.size	IO_dispTab, 28

	.type	Main_dispTab,@object            # @Main_dispTab
	.globl	Main_dispTab
	.p2align	4
Main_dispTab:
	.4byte	Object.abort
	.4byte	Object.type_name
	.4byte	Object.copy
	.4byte	IO.out_string
	.4byte	IO.out_int
	.4byte	IO.in_string
	.4byte	IO.in_int
	.4byte	Main.main
	.size	Main_dispTab, 32

	.type	Int_dispTab,@object             # @Int_dispTab
	.globl	Int_dispTab
	.p2align	3
Int_dispTab:
	.4byte	Object.abort
	.4byte	Object.type_name
	.4byte	Object.copy
	.size	Int_dispTab, 12

	.type	Bool_dispTab,@object            # @Bool_dispTab
	.globl	Bool_dispTab
	.p2align	3
Bool_dispTab:
	.4byte	Object.abort
	.4byte	Object.type_name
	.4byte	Object.copy
	.size	Bool_dispTab, 12

	.type	String_dispTab,@object          # @String_dispTab
	.globl	String_dispTab
	.p2align	4
String_dispTab:
	.4byte	Object.abort
	.4byte	Object.type_name
	.4byte	Object.copy
	.4byte	String.length
	.4byte	String.concat
	.4byte	String.substr
	.size	String_dispTab, 24

	.type	$emptyStr,@object               # @emptyStr
	.section	.rodata.str1.1,"aMS",@progbits,1
$emptyStr:
	.space	1
	.size	$emptyStr, 1

	.type	$abort_format,@object           # @abort_format
$abort_format:
	.asciz	"%s %s\n"
	.size	$abort_format, 7

	.type	$abort_msg,@object              # @abort_msg
$abort_msg:
	.asciz	"Abort called from class"
	.size	$abort_msg, 24

	.type	$format_int,@object             # @format_int
$format_int:
	.asciz	"%d"
	.size	$format_int, 3

	.type	$format_string,@object          # @format_string
$format_string:
	.asciz	"%s"
	.size	$format_string, 3

	.type	$__unnamed_1,@object            # @1
$__unnamed_1:
	.asciz	"%s%s%s"
	.size	$__unnamed_1, 7

	.type	$__unnamed_2,@object            # @2
$__unnamed_2:
	.asciz	":1"
	.size	$__unnamed_2, 3

	.section	".note.GNU-stack","",@progbits
	.text
