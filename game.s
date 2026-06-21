	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 16, 0
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	stp	x24, x23, [sp, #-64]!           ; 16-byte Folded Spill
	stp	x22, x21, [sp, #16]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #32]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	sub	sp, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	mov	w8, #100                        ; =0x64
	mov	w21, #20                        ; =0x14
Lloh0:
	adrp	x19, l_fmtd@PAGE
Lloh1:
	add	x19, x19, l_fmtd@PAGEOFF
	mov	x22, #10                        ; =0xa
Lloh2:
	adrp	x23, l_str@PAGE
Lloh3:
	add	x23, x23, l_str@PAGEOFF
Lloh4:
	adrp	x20, l_fmts@PAGE
Lloh5:
	add	x20, x20, l_fmts@PAGEOFF
	mov	w24, #5                         ; =0x5
	stp	xzr, x8, [x29, #-64]
	b	LBB0_2
LBB0_1:                                 ; %ifcont
                                        ;   in Loop: Header=BB0_2 Depth=1
	ldur	x8, [x29, #-64]
	add	x8, x8, #1
	stur	x8, [x29, #-64]
LBB0_2:                                 ; %whilecond
                                        ; =>This Inner Loop Header: Depth=1
	ldur	x8, [x29, #-64]
	cmp	x8, #4
	b.gt	LBB0_5
; %bb.3:                                ; %whilebody
                                        ;   in Loop: Header=BB0_2 Depth=1
	ldp	x8, x0, [x29, #-64]
	madd	x1, x8, x21, x22
	mov	x8, sp
	sub	x9, x8, #16
	mov	sp, x9
	stur	x1, [x8, #-16]
	bl	_attack
	mov	x8, x0
	stur	x0, [x29, #-56]
	mov	x0, x19
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x0, [x29, #-56]
	bl	_isDead
	cbz	x0, LBB0_1
; %bb.4:                                ; %then
                                        ;   in Loop: Header=BB0_2 Depth=1
	mov	x0, x20
	str	x23, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	stur	x24, [x29, #-64]
	b	LBB0_1
LBB0_5:                                 ; %whileend
	mov	w0, #6                          ; =0x6
	bl	_factorial
	mov	x8, x0
Lloh6:
	adrp	x0, l_fmtd.1@PAGE
Lloh7:
	add	x0, x0, l_fmtd.1@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x0, #-99                        ; =0xffffffffffffff9d
	bl	_abs
	mov	x8, x0
Lloh8:
	adrp	x0, l_fmtd.2@PAGE
Lloh9:
	add	x0, x0, l_fmtd.2@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x0, xzr
	sub	sp, x29, #48
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #32]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #16]             ; 16-byte Folded Reload
	ldp	x24, x23, [sp], #64             ; 16-byte Folded Reload
	ret
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.loh AdrpAdd	Lloh8, Lloh9
	.loh AdrpAdd	Lloh6, Lloh7
	.cfi_endproc
                                        ; -- End function
	.globl	_abs                            ; -- Begin function abs
	.p2align	2
_abs:                                   ; @abs
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	mov	x8, x0
	cmp	x0, #0
	cneg	x0, x0, lt
	str	x8, [sp, #8]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_max                            ; -- Begin function max
	.p2align	2
_max:                                   ; @max
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	cmp	x0, x1
	csel	x8, x0, x1, gt
	stp	x1, x0, [sp], #16
	mov	x0, x8
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_min                            ; -- Begin function min
	.p2align	2
_min:                                   ; @min
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	cmp	x0, x1
	csel	x8, x0, x1, lt
	stp	x1, x0, [sp], #16
	mov	x0, x8
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_pow                            ; -- Begin function pow
	.p2align	2
_pow:                                   ; @pow
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	mov	w8, #1                          ; =0x1
	stp	x1, x0, [sp, #16]
	stp	xzr, x8, [sp]
LBB4_1:                                 ; %whilecond
                                        ; =>This Inner Loop Header: Depth=1
	ldp	x8, x0, [sp]
	ldr	x9, [sp, #16]
	cmp	x8, x9
	b.ge	LBB4_3
; %bb.2:                                ; %whilebody
                                        ;   in Loop: Header=BB4_1 Depth=1
	ldr	x8, [sp, #24]
	ldr	x9, [sp]
	mul	x8, x0, x8
	add	x9, x9, #1
	stp	x9, x8, [sp]
	b	LBB4_1
LBB4_3:                                 ; %whileend
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_factorial                      ; -- Begin function factorial
	.p2align	2
_factorial:                             ; @factorial
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #48
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 48
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	cmp	x0, #1
	str	x0, [sp, #8]
	b.gt	LBB5_2
; %bb.1:
	mov	w0, #1                          ; =0x1
	b	LBB5_3
LBB5_2:                                 ; %ifcont
	ldr	x19, [sp, #8]
	sub	x0, x19, #1
	bl	_factorial
	mul	x0, x19, x0
LBB5_3:                                 ; %common.ret
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_attack                         ; -- Begin function attack
	.p2align	2
_attack:                                ; @attack
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	sub	x8, x0, x1
	stp	x1, x0, [sp, #16]
	cmp	x8, #0
	csel	x0, xzr, x8, lt
	str	x0, [sp, #8]
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_isDead                         ; -- Begin function isDead
	.p2align	2
_isDead:                                ; @isDead
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	mov	x8, x0
	cmp	x0, #1
	cset	w0, lt
	str	x8, [sp, #8]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_fmtd:                                 ; @fmtd
	.asciz	"%lld\n"

l_str:                                  ; @str
	.asciz	"Dead!"

l_fmts:                                 ; @fmts
	.asciz	"%s\n"

l_fmtd.1:                               ; @fmtd.1
	.asciz	"%lld\n"

l_fmtd.2:                               ; @fmtd.2
	.asciz	"%lld\n"

.subsections_via_symbols
