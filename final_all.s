	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 16, 0
	.globl	_double                         ; -- Begin function double
	.p2align	2
_double:                                ; @double
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	mov	x8, x0
	lsl	x0, x0, #1
	str	x8, [sp, #8]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	stp	x28, x27, [sp, #-80]!           ; 16-byte Folded Spill
	stp	x24, x23, [sp, #16]             ; 16-byte Folded Spill
	stp	x22, x21, [sp, #32]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #48]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	sub	sp, sp, #864
	mov	x19, sp
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	.cfi_offset w27, -72
	.cfi_offset w28, -80
	mov	w8, #42                         ; =0x2a
Lloh0:
	adrp	x9, l_str@PAGE
Lloh1:
	add	x9, x9, l_str@PAGEOFF
	stp	x9, x8, [x29, #-80]
	mov	w20, #1                         ; =0x1
	mov	w9, #2                          ; =0x2
	stp	x20, x9, [x19, #24]
	mov	w9, #3                          ; =0x3
	mov	w10, #100                       ; =0x64
	stp	x9, x10, [x29, #-96]
	add	x10, x19, #24
Lloh2:
	adrp	x0, l_fmtd@PAGE
Lloh3:
	add	x0, x0, l_fmtd@PAGEOFF
	str	x9, [x19, #40]
	stur	x10, [x29, #-104]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x29, #-80]
Lloh4:
	adrp	x0, l_fmts@PAGE
Lloh5:
	add	x0, x0, l_fmts@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x29, #-104]
Lloh6:
	adrp	x0, l_fmtd.1@PAGE
Lloh7:
	add	x0, x0, l_fmtd.1@PAGEOFF
	ldr	x8, [x8]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w8, #15                         ; =0xf
Lloh8:
	adrp	x0, l_fmtd.2@PAGE
Lloh9:
	add	x0, x0, l_fmtd.2@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w8, #4                          ; =0x4
Lloh10:
	adrp	x0, l_fmtd.3@PAGE
Lloh11:
	add	x0, x0, l_fmtd.3@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	fmov	d0, #2.00000000
	fmov	d1, #10.00000000
	bl	_pow
	fcvtzs	x8, d0
Lloh12:
	adrp	x0, l_fmtd.4@PAGE
Lloh13:
	add	x0, x0, l_fmtd.4@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x29, #-72]
Lloh14:
	adrp	x0, l_fmtd.5@PAGE
Lloh15:
	add	x0, x0, l_fmtd.5@PAGEOFF
	cmp	x8, #40
	cset	w8, gt
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh16:
	adrp	x0, l_fmtd.6@PAGE
Lloh17:
	add	x0, x0, l_fmtd.6@PAGEOFF
	str	x20, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh18:
	adrp	x0, l_fmtd.7@PAGE
Lloh19:
	add	x0, x0, l_fmtd.7@PAGEOFF
	str	x20, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x29, #-72]
	cmp	x8, #41
	b.lt	LBB1_2
; %bb.1:                                ; %then
	mov	w8, #100                        ; =0x64
Lloh20:
	adrp	x0, l_fmtd.8@PAGE
Lloh21:
	add	x0, x0, l_fmtd.8@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
LBB1_2:                                 ; %ifcont
	mov	x8, sp
	sub	x21, x8, #16
	mov	sp, x21
Lloh22:
	adrp	x20, l_fmtd.9@PAGE
Lloh23:
	add	x20, x20, l_fmtd.9@PAGEOFF
	stur	xzr, [x8, #-16]
LBB1_3:                                 ; %whilecond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	x8, [x21]
	cmp	x8, #2
	b.gt	LBB1_5
; %bb.4:                                ; %whilebody
                                        ;   in Loop: Header=BB1_3 Depth=1
	ldr	x8, [x21]
	mov	x0, x20
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldr	x8, [x21]
	add	x8, x8, #1
	str	x8, [x21]
	b	LBB1_3
LBB1_5:                                 ; %whileend
	mov	x8, sp
	sub	x22, x8, #16
	mov	sp, x22
Lloh24:
	adrp	x20, l_fmtd.10@PAGE
Lloh25:
	add	x20, x20, l_fmtd.10@PAGEOFF
	stur	xzr, [x8, #-16]
LBB1_6:                                 ; %forcond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	x23, [x22]
	ldur	x21, [x29, #-104]
	cmp	x23, #2
	b.gt	LBB1_8
; %bb.7:                                ; %forbody
                                        ;   in Loop: Header=BB1_6 Depth=1
	ldr	x8, [x22]
	mov	x0, x20
	ldr	x8, [x21, x8, lsl #3]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	add	x8, x23, #1
	str	x8, [x22]
	b	LBB1_6
LBB1_8:                                 ; %forend
	ldur	x22, [x29, #-96]
	mov	x8, sp
	sub	x23, x8, #16
	mov	sp, x23
Lloh26:
	adrp	x20, l_fmtd.11@PAGE
Lloh27:
	add	x20, x20, l_fmtd.11@PAGEOFF
	stur	xzr, [x8, #-16]
LBB1_9:                                 ; %forcond19
                                        ; =>This Inner Loop Header: Depth=1
	ldr	x24, [x23]
	cmp	x24, x22
	b.ge	LBB1_11
; %bb.10:                               ; %forbody20
                                        ;   in Loop: Header=BB1_9 Depth=1
	mov	x9, sp
	ldr	x8, [x21, x24, lsl #3]
	sub	x10, x9, #16
	mov	sp, x10
	stur	x8, [x9, #-16]
	mov	x0, x20
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	add	x8, x24, #1
	str	x8, [x23]
	b	LBB1_9
LBB1_11:                                ; %forend21
	mov	w0, #21                         ; =0x15
	bl	_double
	mov	x8, x0
Lloh28:
	adrp	x0, l_fmtd.12@PAGE
Lloh29:
	add	x0, x0, l_fmtd.12@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w0, #5                          ; =0x5
	bl	_factorial
	mov	x8, x0
Lloh30:
	adrp	x0, l_fmtd.13@PAGE
Lloh31:
	add	x0, x0, l_fmtd.13@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x8, sp
	sub	x9, x8, #16
	mov	sp, x9
	mov	w9, #10                         ; =0xa
	mov	w10, #20                        ; =0x14
	stp	x9, x10, [x8, #-16]
	mov	x8, sp
	sub	x11, x8, #16
	mov	sp, x11
	stp	x9, x10, [x8, #-16]
Lloh32:
	adrp	x0, l_fmtd.14@PAGE
Lloh33:
	add	x0, x0, l_fmtd.14@PAGEOFF
	str	x9, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x20, sp
	sub	x8, x20, #16
	mov	sp, x8
	mov	w8, #15                         ; =0xf
Lloh34:
	adrp	x0, l_fmtd.15@PAGE
Lloh35:
	add	x0, x0, l_fmtd.15@PAGEOFF
	stur	x8, [x20, #-16]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x20, #-16]
Lloh36:
	adrp	x0, l_fmtd.16@PAGE
Lloh37:
	add	x0, x0, l_fmtd.16@PAGEOFF
	add	x8, x8, #1
	stur	x8, [x20, #-16]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x20, sp
	sub	x8, x20, #32
	mov	sp, x8
	sub	x8, sp, #800
	mov	sp, x8
	mov	w9, #1                          ; =0x1
	mov	w10, #2                         ; =0x2
	stur	x8, [x20, #-32]
	stp	x9, x10, [x8]
	mov	w9, #100                        ; =0x64
	sub	x8, sp, #32
	stp	x10, x9, [x20, #-24]
	mov	sp, x8
	ldur	x8, [x20, #-32]
	mov	x9, x10
	mov	w10, #3                         ; =0x3
Lloh38:
	adrp	x0, l_fmtd.17@PAGE
Lloh39:
	add	x0, x0, l_fmtd.17@PAGEOFF
	str	x10, [x8, x9, lsl #3]
	add	x9, x9, #1
	ldr	x8, [x8, #16]
	stur	x9, [x20, #-24]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x20, #-24]
Lloh40:
	adrp	x0, l_fmtd.18@PAGE
Lloh41:
	add	x0, x0, l_fmtd.18@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh42:
	adrp	x20, l_str.19@PAGE
Lloh43:
	add	x20, x20, l_str.19@PAGEOFF
	mov	x0, x20
	bl	_strlen
Lloh44:
	adrp	x22, l_str.20@PAGE
Lloh45:
	add	x22, x22, l_str.20@PAGEOFF
	mov	x21, x0
	mov	x0, x22
	bl	_strlen
	add	x8, x21, x0
	add	x0, x8, #1
	bl	_malloc
	mov	x1, x20
	mov	x21, x0
	bl	_strcpy
	mov	x0, x21
	mov	x1, x22
	bl	_strcat
	mov	x8, sp
	sub	x9, x8, #16
	mov	sp, x9
	stur	x21, [x8, #-16]
Lloh46:
	adrp	x0, l_fmts.21@PAGE
Lloh47:
	add	x0, x0, l_fmts.21@PAGEOFF
	str	x21, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x0, #-99                        ; =0xffffffffffffff9d
	bl	_abs
	mov	x8, x0
Lloh48:
	adrp	x0, l_fmtd.22@PAGE
Lloh49:
	add	x0, x0, l_fmtd.22@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w0, #2                          ; =0x2
	mov	w1, #8                          ; =0x8
	bl	_pow
	mov	x8, x0
Lloh50:
	adrp	x0, l_fmtd.23@PAGE
Lloh51:
	add	x0, x0, l_fmtd.23@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w0, #6                          ; =0x6
	bl	_factorial
	mov	x8, x0
Lloh52:
	adrp	x0, l_fmtd.24@PAGE
Lloh53:
	add	x0, x0, l_fmtd.24@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x0, xzr
	sub	sp, x29, #64
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #48]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #32]             ; 16-byte Folded Reload
	ldp	x24, x23, [sp, #16]             ; 16-byte Folded Reload
	ldp	x28, x27, [sp], #80             ; 16-byte Folded Reload
	ret
	.loh AdrpAdd	Lloh18, Lloh19
	.loh AdrpAdd	Lloh16, Lloh17
	.loh AdrpAdd	Lloh14, Lloh15
	.loh AdrpAdd	Lloh12, Lloh13
	.loh AdrpAdd	Lloh10, Lloh11
	.loh AdrpAdd	Lloh8, Lloh9
	.loh AdrpAdd	Lloh6, Lloh7
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.loh AdrpAdd	Lloh20, Lloh21
	.loh AdrpAdd	Lloh22, Lloh23
	.loh AdrpAdd	Lloh24, Lloh25
	.loh AdrpAdd	Lloh26, Lloh27
	.loh AdrpAdd	Lloh52, Lloh53
	.loh AdrpAdd	Lloh50, Lloh51
	.loh AdrpAdd	Lloh48, Lloh49
	.loh AdrpAdd	Lloh46, Lloh47
	.loh AdrpAdd	Lloh44, Lloh45
	.loh AdrpAdd	Lloh42, Lloh43
	.loh AdrpAdd	Lloh40, Lloh41
	.loh AdrpAdd	Lloh38, Lloh39
	.loh AdrpAdd	Lloh36, Lloh37
	.loh AdrpAdd	Lloh34, Lloh35
	.loh AdrpAdd	Lloh32, Lloh33
	.loh AdrpAdd	Lloh30, Lloh31
	.loh AdrpAdd	Lloh28, Lloh29
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
LBB5_1:                                 ; %whilecond
                                        ; =>This Inner Loop Header: Depth=1
	ldp	x8, x0, [sp]
	ldr	x9, [sp, #16]
	cmp	x8, x9
	b.ge	LBB5_3
; %bb.2:                                ; %whilebody
                                        ;   in Loop: Header=BB5_1 Depth=1
	ldr	x8, [sp, #24]
	ldr	x9, [sp]
	mul	x8, x0, x8
	add	x9, x9, #1
	stp	x9, x8, [sp]
	b	LBB5_1
LBB5_3:                                 ; %whileend
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
	b.gt	LBB6_2
; %bb.1:
	mov	w0, #1                          ; =0x1
	b	LBB6_3
LBB6_2:                                 ; %ifcont
	ldr	x19, [sp, #8]
	sub	x0, x19, #1
	bl	_factorial
	mul	x0, x19, x0
LBB6_3:                                 ; %common.ret
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_str:                                  ; @str
	.asciz	"Chaos"

l_fmtd:                                 ; @fmtd
	.asciz	"%d\n"

l_fmts:                                 ; @fmts
	.asciz	"%s\n"

l_fmtd.1:                               ; @fmtd.1
	.asciz	"%d\n"

l_fmtd.2:                               ; @fmtd.2
	.asciz	"%d\n"

l_fmtd.3:                               ; @fmtd.3
	.asciz	"%d\n"

l_fmtd.4:                               ; @fmtd.4
	.asciz	"%d\n"

l_fmtd.5:                               ; @fmtd.5
	.asciz	"%d\n"

l_fmtd.6:                               ; @fmtd.6
	.asciz	"%d\n"

l_fmtd.7:                               ; @fmtd.7
	.asciz	"%d\n"

l_fmtd.8:                               ; @fmtd.8
	.asciz	"%d\n"

l_fmtd.9:                               ; @fmtd.9
	.asciz	"%d\n"

l_fmtd.10:                              ; @fmtd.10
	.asciz	"%d\n"

l_fmtd.11:                              ; @fmtd.11
	.asciz	"%d\n"

l_fmtd.12:                              ; @fmtd.12
	.asciz	"%d\n"

l_fmtd.13:                              ; @fmtd.13
	.asciz	"%d\n"

l_fmtd.14:                              ; @fmtd.14
	.asciz	"%d\n"

l_fmtd.15:                              ; @fmtd.15
	.asciz	"%d\n"

l_fmtd.16:                              ; @fmtd.16
	.asciz	"%d\n"

l_fmtd.17:                              ; @fmtd.17
	.asciz	"%d\n"

l_fmtd.18:                              ; @fmtd.18
	.asciz	"%d\n"

l_str.19:                               ; @str.19
	.asciz	"Hello "

l_str.20:                               ; @str.20
	.asciz	"World"

l_fmts.21:                              ; @fmts.21
	.asciz	"%s\n"

l_fmtd.22:                              ; @fmtd.22
	.asciz	"%d\n"

l_fmtd.23:                              ; @fmtd.23
	.asciz	"%d\n"

l_fmtd.24:                              ; @fmtd.24
	.asciz	"%d\n"

.subsections_via_symbols
