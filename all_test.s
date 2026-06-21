	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 16, 0
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	stp	x28, x27, [sp, #-64]!           ; 16-byte Folded Spill
	stp	x22, x21, [sp, #16]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #32]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	sub	sp, sp, #880
	mov	x19, sp
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w27, -56
	.cfi_offset w28, -64
Lloh0:
	adrp	x8, l_str@PAGE
Lloh1:
	add	x8, x8, l_str@PAGEOFF
Lloh2:
	adrp	x0, l_fmts@PAGE
Lloh3:
	add	x0, x0, l_fmts@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w21, #42                        ; =0x2a
Lloh4:
	adrp	x8, l_str.3@PAGE
Lloh5:
	add	x8, x8, l_str.3@PAGEOFF
	stp	x8, x21, [x29, #-64]
	mov	w20, #1                         ; =0x1
	mov	w8, #2                          ; =0x2
	stp	x20, x8, [x19, #32]
	mov	w8, #3                          ; =0x3
	mov	w9, #100                        ; =0x64
	stp	x8, x9, [x29, #-88]
	add	x9, x19, #32
Lloh6:
	adrp	x0, l_fmtd@PAGE
Lloh7:
	add	x0, x0, l_fmtd@PAGEOFF
	sturb	w20, [x29, #-65]
	str	x8, [x19, #48]
	stur	x9, [x29, #-96]
	str	x21, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x29, #-64]
Lloh8:
	adrp	x0, l_fmts.4@PAGE
Lloh9:
	add	x0, x0, l_fmts.4@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldurb	w8, [x29, #-65]
Lloh10:
	adrp	x0, l_fmtd.5@PAGE
Lloh11:
	add	x0, x0, l_fmtd.5@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x0, [x29, #-64]
	bl	_strlen
	mov	x8, x0
Lloh12:
	adrp	x0, l_fmtd.6@PAGE
Lloh13:
	add	x0, x0, l_fmtd.6@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh14:
	adrp	x8, l_str.7@PAGE
Lloh15:
	add	x8, x8, l_str.7@PAGEOFF
Lloh16:
	adrp	x0, l_fmts.8@PAGE
Lloh17:
	add	x0, x0, l_fmts.8@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w8, #15                         ; =0xf
Lloh18:
	adrp	x0, l_fmtd.9@PAGE
Lloh19:
	add	x0, x0, l_fmtd.9@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w8, #12                         ; =0xc
Lloh20:
	adrp	x0, l_fmtd.10@PAGE
Lloh21:
	add	x0, x0, l_fmtd.10@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh22:
	adrp	x0, l_fmtd.11@PAGE
Lloh23:
	add	x0, x0, l_fmtd.11@PAGEOFF
	str	x21, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w8, #25                         ; =0x19
Lloh24:
	adrp	x0, l_fmtd.12@PAGE
Lloh25:
	add	x0, x0, l_fmtd.12@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w8, #4                          ; =0x4
Lloh26:
	adrp	x0, l_fmtd.13@PAGE
Lloh27:
	add	x0, x0, l_fmtd.13@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh28:
	adrp	x8, l_str.14@PAGE
Lloh29:
	add	x8, x8, l_str.14@PAGEOFF
Lloh30:
	adrp	x0, l_fmts.15@PAGE
Lloh31:
	add	x0, x0, l_fmts.15@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x29, #-56]
Lloh32:
	adrp	x0, l_fmtd.16@PAGE
Lloh33:
	add	x0, x0, l_fmtd.16@PAGEOFF
	cmp	x8, #40
	cset	w8, gt
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x29, #-56]
Lloh34:
	adrp	x0, l_fmtd.17@PAGE
Lloh35:
	add	x0, x0, l_fmtd.17@PAGEOFF
	cmp	x8, #50
	cset	w8, lt
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x29, #-56]
Lloh36:
	adrp	x0, l_fmtd.18@PAGE
Lloh37:
	add	x0, x0, l_fmtd.18@PAGEOFF
	cmp	x8, #42
	cset	w8, eq
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x29, #-56]
Lloh38:
	adrp	x0, l_fmtd.19@PAGE
Lloh39:
	add	x0, x0, l_fmtd.19@PAGEOFF
	cmp	x8, #10
	cset	w8, ne
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh40:
	adrp	x8, l_str.20@PAGE
Lloh41:
	add	x8, x8, l_str.20@PAGEOFF
Lloh42:
	adrp	x0, l_fmts.21@PAGE
Lloh43:
	add	x0, x0, l_fmts.21@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh44:
	adrp	x0, l_fmtd.22@PAGE
Lloh45:
	add	x0, x0, l_fmtd.22@PAGEOFF
	str	x20, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh46:
	adrp	x0, l_fmtd.23@PAGE
Lloh47:
	add	x0, x0, l_fmtd.23@PAGEOFF
	str	x20, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh48:
	adrp	x0, l_fmtd.24@PAGE
Lloh49:
	add	x0, x0, l_fmtd.24@PAGEOFF
	str	x20, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh50:
	adrp	x8, l_str.25@PAGE
Lloh51:
	add	x8, x8, l_str.25@PAGEOFF
Lloh52:
	adrp	x0, l_fmts.26@PAGE
Lloh53:
	add	x0, x0, l_fmts.26@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x29, #-56]
	sub	sp, sp, #16
	cmp	x8, #41
	b.lt	LBB0_2
; %bb.1:                                ; %then
	mov	w8, #100                        ; =0x64
Lloh54:
	adrp	x0, l_fmtd.27@PAGE
Lloh55:
	add	x0, x0, l_fmtd.27@PAGEOFF
	b	LBB0_3
LBB0_2:                                 ; %else
	mov	w8, #200                        ; =0xc8
Lloh56:
	adrp	x0, l_fmtd.28@PAGE
Lloh57:
	add	x0, x0, l_fmtd.28@PAGEOFF
LBB0_3:                                 ; %ifcont
	str	x8, [sp]
	bl	_printf
	add	sp, sp, #16
Lloh58:
	adrp	x8, l_str.29@PAGE
Lloh59:
	add	x8, x8, l_str.29@PAGEOFF
Lloh60:
	adrp	x0, l_fmts.30@PAGE
Lloh61:
	add	x0, x0, l_fmts.30@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x8, sp
	sub	x21, x8, #16
	mov	sp, x21
	mov	w9, #3                          ; =0x3
Lloh62:
	adrp	x20, l_fmtd.31@PAGE
Lloh63:
	add	x20, x20, l_fmtd.31@PAGEOFF
	stur	x9, [x8, #-16]
LBB0_4:                                 ; %whilecond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	x8, [x21]
	cmp	x8, #1
	b.lt	LBB0_6
; %bb.5:                                ; %whilebody
                                        ;   in Loop: Header=BB0_4 Depth=1
	ldr	x8, [x21]
	mov	x0, x20
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldr	x8, [x21]
	sub	x8, x8, #1
	str	x8, [x21]
	b	LBB0_4
LBB0_6:                                 ; %whileend
Lloh64:
	adrp	x8, l_str.32@PAGE
Lloh65:
	add	x8, x8, l_str.32@PAGEOFF
Lloh66:
	adrp	x0, l_fmts.33@PAGE
Lloh67:
	add	x0, x0, l_fmts.33@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x8, sp
	sub	x21, x8, #16
	mov	sp, x21
Lloh68:
	adrp	x20, l_fmtd.34@PAGE
Lloh69:
	add	x20, x20, l_fmtd.34@PAGEOFF
	stur	xzr, [x8, #-16]
LBB0_7:                                 ; %forcond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	x22, [x21]
	cmp	x22, #2
	b.gt	LBB0_9
; %bb.8:                                ; %forbody
                                        ;   in Loop: Header=BB0_7 Depth=1
	ldur	x8, [x29, #-96]
	ldr	x9, [x21]
	mov	x0, x20
	ldr	x8, [x8, x9, lsl #3]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	add	x8, x22, #1
	str	x8, [x21]
	b	LBB0_7
LBB0_9:                                 ; %forend
Lloh70:
	adrp	x8, l_str.35@PAGE
Lloh71:
	add	x8, x8, l_str.35@PAGEOFF
Lloh72:
	adrp	x0, l_fmts.36@PAGE
Lloh73:
	add	x0, x0, l_fmts.36@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w0, #21                         ; =0x15
	bl	_double
	mov	x8, x0
Lloh74:
	adrp	x0, l_fmtd.37@PAGE
Lloh75:
	add	x0, x0, l_fmtd.37@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh76:
	adrp	x8, l_str.38@PAGE
Lloh77:
	add	x8, x8, l_str.38@PAGEOFF
Lloh78:
	adrp	x0, l_fmts.39@PAGE
Lloh79:
	add	x0, x0, l_fmts.39@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w0, #5                          ; =0x5
	mov	w20, #5                         ; =0x5
	bl	_factorial
	mov	x8, x0
Lloh80:
	adrp	x0, l_fmtd.40@PAGE
Lloh81:
	add	x0, x0, l_fmtd.40@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh82:
	adrp	x8, l_str.41@PAGE
Lloh83:
	add	x8, x8, l_str.41@PAGEOFF
Lloh84:
	adrp	x0, l_fmts.42@PAGE
Lloh85:
	add	x0, x0, l_fmts.42@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x8, sp
	sub	x9, x8, #16
	mov	sp, x9
	mov	w9, #10                         ; =0xa
	mov	w10, #20                        ; =0x14
	mov	x21, sp
	stp	x9, x10, [x8, #-16]
	sub	x8, x21, #16
	mov	sp, x8
	stp	x9, x10, [x21, #-16]
Lloh86:
	adrp	x0, l_fmtd.43@PAGE
Lloh87:
	add	x0, x0, l_fmtd.43@PAGEOFF
	str	x9, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x21, #-8]
Lloh88:
	adrp	x0, l_fmtd.44@PAGE
Lloh89:
	add	x0, x0, l_fmtd.44@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh90:
	adrp	x8, l_str.45@PAGE
Lloh91:
	add	x8, x8, l_str.45@PAGEOFF
Lloh92:
	adrp	x0, l_fmts.46@PAGE
Lloh93:
	add	x0, x0, l_fmts.46@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x21, sp
	sub	x8, x21, #32
	mov	sp, x8
	sub	x8, sp, #800
	mov	sp, x8
	mov	w9, #1                          ; =0x1
	mov	w10, #2                         ; =0x2
	stur	x8, [x21, #-32]
	stp	x9, x10, [x8]
	mov	w9, #3                          ; =0x3
	mov	w10, #100                       ; =0x64
	str	x9, [x8, #16]
	sub	x8, sp, #32
	stp	x9, x10, [x21, #-24]
	mov	sp, x8
	ldur	x8, [x21, #-32]
Lloh94:
	adrp	x0, l_fmtd.47@PAGE
Lloh95:
	add	x0, x0, l_fmtd.47@PAGEOFF
	ldr	x9, [x8]
	str	x20, [x8, #24]
	str	x9, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x21, #-32]
Lloh96:
	adrp	x0, l_fmtd.48@PAGE
Lloh97:
	add	x0, x0, l_fmtd.48@PAGEOFF
	ldr	x8, [x8, #8]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x21, #-32]
Lloh98:
	adrp	x0, l_fmtd.49@PAGE
Lloh99:
	add	x0, x0, l_fmtd.49@PAGEOFF
	ldr	x8, [x8, #16]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x21, #-32]
Lloh100:
	adrp	x0, l_fmtd.50@PAGE
Lloh101:
	add	x0, x0, l_fmtd.50@PAGEOFF
	ldr	x8, [x8, #24]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	ldur	x8, [x21, #-32]
Lloh102:
	adrp	x0, l_fmtd.51@PAGE
Lloh103:
	add	x0, x0, l_fmtd.51@PAGEOFF
	ldr	x8, [x8, #32]
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh104:
	adrp	x8, l_str.52@PAGE
Lloh105:
	add	x8, x8, l_str.52@PAGEOFF
Lloh106:
	adrp	x0, l_fmts.53@PAGE
Lloh107:
	add	x0, x0, l_fmts.53@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x8, sp
	sub	x9, x8, #16
	mov	sp, x9
Lloh108:
	adrp	x9, l_str.54@PAGE
Lloh109:
	add	x9, x9, l_str.54@PAGEOFF
	stur	x9, [x8, #-16]
	mov	x9, sp
	sub	x10, x9, #16
	mov	sp, x10
	ldur	x20, [x8, #-16]
Lloh110:
	adrp	x21, l_str.55@PAGE
Lloh111:
	add	x21, x21, l_str.55@PAGEOFF
	stur	x21, [x9, #-16]
	mov	x0, x20
	bl	_strlen
	mov	x22, x0
	mov	x0, x21
	bl	_strlen
	add	x8, x22, x0
	add	x0, x8, #1
	bl	_malloc
	mov	x1, x20
	mov	x22, x0
	bl	_strcpy
	mov	x0, x22
	mov	x1, x21
	bl	_strcat
	mov	x8, sp
	sub	x9, x8, #16
	mov	sp, x9
	stur	x22, [x8, #-16]
Lloh112:
	adrp	x0, l_fmts.56@PAGE
Lloh113:
	add	x0, x0, l_fmts.56@PAGEOFF
	str	x22, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh114:
	adrp	x8, l_str.57@PAGE
Lloh115:
	add	x8, x8, l_str.57@PAGEOFF
Lloh116:
	adrp	x0, l_fmts.58@PAGE
Lloh117:
	add	x0, x0, l_fmts.58@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x0, #-99                        ; =0xffffffffffffff9d
	bl	_abs
	mov	x8, x0
Lloh118:
	adrp	x0, l_fmtd.59@PAGE
Lloh119:
	add	x0, x0, l_fmtd.59@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w0, #10                         ; =0xa
	mov	w1, #30                         ; =0x1e
	bl	_max
	mov	x8, x0
Lloh120:
	adrp	x0, l_fmtd.60@PAGE
Lloh121:
	add	x0, x0, l_fmtd.60@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	w0, #2                          ; =0x2
	mov	w1, #8                          ; =0x8
	bl	_pow
	mov	x8, x0
Lloh122:
	adrp	x0, l_fmtd.61@PAGE
Lloh123:
	add	x0, x0, l_fmtd.61@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
Lloh124:
	adrp	x8, l_str.62@PAGE
Lloh125:
	add	x8, x8, l_str.62@PAGEOFF
Lloh126:
	adrp	x0, l_fmts.63@PAGE
Lloh127:
	add	x0, x0, l_fmts.63@PAGEOFF
	str	x8, [sp, #-16]!
	bl	_printf
	add	sp, sp, #16
	mov	x0, xzr
	sub	sp, x29, #48
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #32]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #16]             ; 16-byte Folded Reload
	ldp	x28, x27, [sp], #64             ; 16-byte Folded Reload
	ret
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
	.loh AdrpAdd	Lloh26, Lloh27
	.loh AdrpAdd	Lloh24, Lloh25
	.loh AdrpAdd	Lloh22, Lloh23
	.loh AdrpAdd	Lloh20, Lloh21
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
	.loh AdrpAdd	Lloh54, Lloh55
	.loh AdrpAdd	Lloh56, Lloh57
	.loh AdrpAdd	Lloh62, Lloh63
	.loh AdrpAdd	Lloh60, Lloh61
	.loh AdrpAdd	Lloh58, Lloh59
	.loh AdrpAdd	Lloh68, Lloh69
	.loh AdrpAdd	Lloh66, Lloh67
	.loh AdrpAdd	Lloh64, Lloh65
	.loh AdrpAdd	Lloh126, Lloh127
	.loh AdrpAdd	Lloh124, Lloh125
	.loh AdrpAdd	Lloh122, Lloh123
	.loh AdrpAdd	Lloh120, Lloh121
	.loh AdrpAdd	Lloh118, Lloh119
	.loh AdrpAdd	Lloh116, Lloh117
	.loh AdrpAdd	Lloh114, Lloh115
	.loh AdrpAdd	Lloh112, Lloh113
	.loh AdrpAdd	Lloh110, Lloh111
	.loh AdrpAdd	Lloh108, Lloh109
	.loh AdrpAdd	Lloh106, Lloh107
	.loh AdrpAdd	Lloh104, Lloh105
	.loh AdrpAdd	Lloh102, Lloh103
	.loh AdrpAdd	Lloh100, Lloh101
	.loh AdrpAdd	Lloh98, Lloh99
	.loh AdrpAdd	Lloh96, Lloh97
	.loh AdrpAdd	Lloh94, Lloh95
	.loh AdrpAdd	Lloh92, Lloh93
	.loh AdrpAdd	Lloh90, Lloh91
	.loh AdrpAdd	Lloh88, Lloh89
	.loh AdrpAdd	Lloh86, Lloh87
	.loh AdrpAdd	Lloh84, Lloh85
	.loh AdrpAdd	Lloh82, Lloh83
	.loh AdrpAdd	Lloh80, Lloh81
	.loh AdrpAdd	Lloh78, Lloh79
	.loh AdrpAdd	Lloh76, Lloh77
	.loh AdrpAdd	Lloh74, Lloh75
	.loh AdrpAdd	Lloh72, Lloh73
	.loh AdrpAdd	Lloh70, Lloh71
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
	.section	__TEXT,__cstring,cstring_literals
l_str:                                  ; @str
	.asciz	"=== \353\263\200\354\210\230 ==="

l_fmts:                                 ; @fmts
	.asciz	"%s\n"

l_str.3:                                ; @str.3
	.asciz	"Chaos"

l_fmtd:                                 ; @fmtd
	.asciz	"%lld\n"

l_fmts.4:                               ; @fmts.4
	.asciz	"%s\n"

l_fmtd.5:                               ; @fmtd.5
	.asciz	"%lld\n"

l_fmtd.6:                               ; @fmtd.6
	.asciz	"%lld\n"

l_str.7:                                ; @str.7
	.asciz	"=== \354\227\260\354\202\260 ==="

l_fmts.8:                               ; @fmts.8
	.asciz	"%s\n"

l_fmtd.9:                               ; @fmtd.9
	.asciz	"%lld\n"

l_fmtd.10:                              ; @fmtd.10
	.asciz	"%lld\n"

l_fmtd.11:                              ; @fmtd.11
	.asciz	"%lld\n"

l_fmtd.12:                              ; @fmtd.12
	.asciz	"%lld\n"

l_fmtd.13:                              ; @fmtd.13
	.asciz	"%lld\n"

l_str.14:                               ; @str.14
	.asciz	"=== \353\271\204\352\265\220 ==="

l_fmts.15:                              ; @fmts.15
	.asciz	"%s\n"

l_fmtd.16:                              ; @fmtd.16
	.asciz	"%lld\n"

l_fmtd.17:                              ; @fmtd.17
	.asciz	"%lld\n"

l_fmtd.18:                              ; @fmtd.18
	.asciz	"%lld\n"

l_fmtd.19:                              ; @fmtd.19
	.asciz	"%lld\n"

l_str.20:                               ; @str.20
	.asciz	"=== \353\205\274\353\246\254 ==="

l_fmts.21:                              ; @fmts.21
	.asciz	"%s\n"

l_fmtd.22:                              ; @fmtd.22
	.asciz	"%lld\n"

l_fmtd.23:                              ; @fmtd.23
	.asciz	"%lld\n"

l_fmtd.24:                              ; @fmtd.24
	.asciz	"%lld\n"

l_str.25:                               ; @str.25
	.asciz	"=== if/else ==="

l_fmts.26:                              ; @fmts.26
	.asciz	"%s\n"

l_fmtd.27:                              ; @fmtd.27
	.asciz	"%lld\n"

l_fmtd.28:                              ; @fmtd.28
	.asciz	"%lld\n"

l_str.29:                               ; @str.29
	.asciz	"=== while ==="

l_fmts.30:                              ; @fmts.30
	.asciz	"%s\n"

l_fmtd.31:                              ; @fmtd.31
	.asciz	"%lld\n"

l_str.32:                               ; @str.32
	.asciz	"=== for ==="

l_fmts.33:                              ; @fmts.33
	.asciz	"%s\n"

l_fmtd.34:                              ; @fmtd.34
	.asciz	"%lld\n"

l_str.35:                               ; @str.35
	.asciz	"=== \355\225\250\354\210\230 ==="

l_fmts.36:                              ; @fmts.36
	.asciz	"%s\n"

l_fmtd.37:                              ; @fmtd.37
	.asciz	"%lld\n"

l_str.38:                               ; @str.38
	.asciz	"=== \354\236\254\352\267\200 ==="

l_fmts.39:                              ; @fmts.39
	.asciz	"%s\n"

l_fmtd.40:                              ; @fmtd.40
	.asciz	"%lld\n"

l_str.41:                               ; @str.41
	.asciz	"=== \352\265\254\354\241\260\354\262\264 ==="

l_fmts.42:                              ; @fmts.42
	.asciz	"%s\n"

l_fmtd.43:                              ; @fmtd.43
	.asciz	"%lld\n"

l_fmtd.44:                              ; @fmtd.44
	.asciz	"%lld\n"

l_str.45:                               ; @str.45
	.asciz	"=== \353\246\254\354\212\244\355\212\270 push ==="

l_fmts.46:                              ; @fmts.46
	.asciz	"%s\n"

l_fmtd.47:                              ; @fmtd.47
	.asciz	"%lld\n"

l_fmtd.48:                              ; @fmtd.48
	.asciz	"%lld\n"

l_fmtd.49:                              ; @fmtd.49
	.asciz	"%lld\n"

l_fmtd.50:                              ; @fmtd.50
	.asciz	"%lld\n"

l_fmtd.51:                              ; @fmtd.51
	.asciz	"%lld\n"

l_str.52:                               ; @str.52
	.asciz	"=== concat ==="

l_fmts.53:                              ; @fmts.53
	.asciz	"%s\n"

l_str.54:                               ; @str.54
	.asciz	"Hello "

l_str.55:                               ; @str.55
	.asciz	"World"

l_fmts.56:                              ; @fmts.56
	.asciz	"%s\n"

l_str.57:                               ; @str.57
	.asciz	"=== import ==="

l_fmts.58:                              ; @fmts.58
	.asciz	"%s\n"

l_fmtd.59:                              ; @fmtd.59
	.asciz	"%lld\n"

l_fmtd.60:                              ; @fmtd.60
	.asciz	"%lld\n"

l_fmtd.61:                              ; @fmtd.61
	.asciz	"%lld\n"

l_str.62:                               ; @str.62
	.asciz	"=== \354\231\204\353\243\214 ==="

l_fmts.63:                              ; @fmts.63
	.asciz	"%s\n"

.subsections_via_symbols
