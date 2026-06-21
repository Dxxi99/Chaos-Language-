	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 16, 0
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	stp	x28, x27, [sp, #-32]!           ; 16-byte Folded Spill
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	sub	sp, sp, #880
	.cfi_def_cfa_offset 912
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w27, -24
	.cfi_offset w28, -32
	mov	w8, #1                          ; =0x1
	mov	w9, #2                          ; =0x2
	stp	xzr, xzr, [sp, #16]
	stp	x8, x9, [sp, #56]
	mov	w8, #100                        ; =0x64
	mov	w9, #3                          ; =0x3
	str	x8, [sp, #872]
	add	x8, sp, #56
	str	x8, [sp, #856]
	mov	w8, #5                          ; =0x5
	str	x9, [sp, #864]
	stp	x9, x8, [sp, #72]
LBB0_1:                                 ; %forcond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #16]
	cmp	x8, #4
	b.gt	LBB0_3
; %bb.2:                                ; %forbody
                                        ;   in Loop: Header=BB0_1 Depth=1
	ldp	x10, x11, [sp, #16]
	add	x8, x8, #1
	ldr	x9, [sp, #856]
	ldr	x9, [x9, x10, lsl #3]
	add	x9, x11, x9
	stp	x8, x9, [sp, #16]
	b	LBB0_1
LBB0_3:                                 ; %forend
	mov	w0, #10                         ; =0xa
	bl	_fib
	mov	x8, x0
Lloh0:
	adrp	x0, l_fmtd@PAGE
Lloh1:
	add	x0, x0, l_fmtd@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w0, #7                          ; =0x7
	bl	_isPrime
	mov	x8, x0
Lloh2:
	adrp	x0, l_fmtd.1@PAGE
Lloh3:
	add	x0, x0, l_fmtd.1@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w0, #10                         ; =0xa
	bl	_isPrime
	mov	x8, x0
Lloh4:
	adrp	x0, l_fmtd.2@PAGE
Lloh5:
	add	x0, x0, l_fmtd.2@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w0, #48                         ; =0x30
	mov	w1, #18                         ; =0x12
	bl	_gcd
	mov	x8, x0
Lloh6:
	adrp	x0, l_fmtd.3@PAGE
Lloh7:
	add	x0, x0, l_fmtd.3@PAGEOFF
	str	x8, [sp]
	bl	_printf
	ldr	x8, [sp, #24]
Lloh8:
	adrp	x0, l_fmtd.4@PAGE
Lloh9:
	add	x0, x0, l_fmtd.4@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w0, #8                          ; =0x8
	bl	_factorial
	mov	x8, x0
Lloh10:
	adrp	x0, l_fmtd.5@PAGE
Lloh11:
	add	x0, x0, l_fmtd.5@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	x0, #-123                       ; =0xffffffffffffff85
	bl	_abs
	mov	x8, x0
Lloh12:
	adrp	x0, l_fmtd.6@PAGE
Lloh13:
	add	x0, x0, l_fmtd.6@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	x0, xzr
	add	sp, sp, #880
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x28, x27, [sp], #32             ; 16-byte Folded Reload
	ret
	.loh AdrpAdd	Lloh12, Lloh13
	.loh AdrpAdd	Lloh10, Lloh11
	.loh AdrpAdd	Lloh8, Lloh9
	.loh AdrpAdd	Lloh6, Lloh7
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
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
	.globl	_fib                            ; -- Begin function fib
	.p2align	2
_fib:                                   ; @fib
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
	subs	x8, x0, #1
	str	x0, [sp, #8]
	b.le	LBB6_2
; %bb.1:                                ; %ifcont
	mov	x0, x8
	bl	_fib
	ldr	x8, [sp, #8]
	mov	x19, x0
	sub	x0, x8, #2
	bl	_fib
	add	x0, x19, x0
LBB6_2:                                 ; %common.ret
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_isPrime                        ; -- Begin function isPrime
	.p2align	2
_isPrime:                               ; @isPrime
	.cfi_startproc
; %bb.0:                                ; %entry
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	mov	x29, sp
	sub	sp, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	cmp	x0, #1
	stur	x0, [x29, #-8]
	b.gt	LBB7_2
LBB7_1:
	mov	x0, xzr
	b	LBB7_4
LBB7_2:                                 ; %ifcont
	ldur	x8, [x29, #-8]
	cmp	x8, #2
	b.ne	LBB7_5
; %bb.3:
	mov	w0, #1                          ; =0x1
LBB7_4:                                 ; %common.ret
	mov	sp, x29
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
LBB7_5:                                 ; %ifcont6
	mov	x9, sp
	sub	x8, x9, #16
	mov	sp, x8
	mov	w10, #2                         ; =0x2
	mov	w0, #1                          ; =0x1
	stur	x10, [x9, #-16]
LBB7_6:                                 ; %whilecond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	x9, [x8]
	ldur	x10, [x29, #-8]
	cmp	x9, x10
	b.ge	LBB7_4
; %bb.7:                                ; %whilebody
                                        ;   in Loop: Header=BB7_6 Depth=1
	ldur	x9, [x29, #-8]
	ldr	x10, [x8]
	sdiv	x11, x9, x10
	msub	x9, x11, x10, x9
	cbz	x9, LBB7_1
; %bb.8:                                ; %ifcont16
                                        ;   in Loop: Header=BB7_6 Depth=1
	ldr	x9, [x8]
	add	x9, x9, #1
	str	x9, [x8]
	b	LBB7_6
	.cfi_endproc
                                        ; -- End function
	.globl	_gcd                            ; -- Begin function gcd
	.p2align	2
_gcd:                                   ; @gcd
	.cfi_startproc
; %bb.0:                                ; %entry
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	mov	x29, sp
	sub	sp, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stp	x1, x0, [x29, #-16]
	ldur	x8, [x29, #-16]
	cbz	x8, LBB8_2
LBB8_1:                                 ; %whilebody
                                        ; =>This Inner Loop Header: Depth=1
	mov	x9, sp
	sub	x10, x9, #16
	mov	sp, x10
	ldp	x8, x10, [x29, #-16]
	ldur	x11, [x29, #-16]
	sdiv	x12, x10, x11
	stur	x8, [x9, #-16]
	msub	x10, x12, x11, x10
	stp	x10, x8, [x29, #-16]
	ldur	x8, [x29, #-16]
	cbnz	x8, LBB8_1
LBB8_2:                                 ; %whileend
	ldur	x0, [x29, #-8]
	mov	sp, x29
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_fmtd:                                 ; @fmtd
	.asciz	"%lld\n"

l_fmtd.1:                               ; @fmtd.1
	.asciz	"%lld\n"

l_fmtd.2:                               ; @fmtd.2
	.asciz	"%lld\n"

l_fmtd.3:                               ; @fmtd.3
	.asciz	"%lld\n"

l_fmtd.4:                               ; @fmtd.4
	.asciz	"%lld\n"

l_fmtd.5:                               ; @fmtd.5
	.asciz	"%lld\n"

l_fmtd.6:                               ; @fmtd.6
	.asciz	"%lld\n"

.subsections_via_symbols
