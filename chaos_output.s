	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 16, 0
	.globl	_abs                            ; -- Begin function abs
	.p2align	2
_abs:                                   ; @abs
	.cfi_startproc
; %bb.0:                                ; %e
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
; %bb.0:                                ; %e
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
; %bb.0:                                ; %e
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
; %bb.0:                                ; %e
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	mov	w8, #1                          ; =0x1
	stp	x1, x0, [sp, #16]
	stp	xzr, x8, [sp]
LBB3_1:                                 ; %wc
                                        ; =>This Inner Loop Header: Depth=1
	ldp	x8, x0, [sp]
	ldr	x9, [sp, #16]
	cmp	x8, x9
	b.ge	LBB3_3
; %bb.2:                                ; %wb
                                        ;   in Loop: Header=BB3_1 Depth=1
	ldr	x8, [sp, #24]
	ldr	x9, [sp]
	mul	x8, x0, x8
	add	x9, x9, #1
	stp	x9, x8, [sp]
	b	LBB3_1
LBB3_3:                                 ; %we
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_factorial                      ; -- Begin function factorial
	.p2align	2
_factorial:                             ; @factorial
	.cfi_startproc
; %bb.0:                                ; %e
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
	b.gt	LBB4_2
; %bb.1:
	mov	w0, #1                          ; =0x1
	b	LBB4_3
LBB4_2:                                 ; %m
	ldr	x19, [sp, #8]
	sub	x0, x19, #1
	bl	_factorial
	mul	x0, x19, x0
LBB4_3:                                 ; %common.ret
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
; %bb.0:                                ; %e
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
; %bb.0:                                ; %e
	stp	x22, x21, [sp, #-48]!           ; 16-byte Folded Spill
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	sub	sp, sp, #976
	.cfi_def_cfa_offset 1024
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
Lloh0:
	adrp	x0, l___unnamed_1@PAGE
Lloh1:
	add	x0, x0, l___unnamed_1@PAGEOFF
Lloh2:
	adrp	x8, l_s@PAGE
Lloh3:
	add	x8, x8, l_s@PAGEOFF
	str	x8, [sp]
	bl	_printf
Lloh4:
	adrp	x8, l_s.1@PAGE
Lloh5:
	add	x8, x8, l_s.1@PAGEOFF
	mov	w9, #2                          ; =0x2
	str	x8, [sp, #960]
	mov	w8, #1                          ; =0x1
	mov	w19, #42                        ; =0x2a
	stp	x8, x9, [sp, #128]
	mov	w9, #100                        ; =0x64
Lloh6:
	adrp	x0, l___unnamed_2@PAGE
Lloh7:
	add	x0, x0, l___unnamed_2@PAGEOFF
	strb	w8, [sp, #959]
	mov	w8, #3                          ; =0x3
	str	x9, [sp, #944]
	add	x9, sp, #128
	str	x19, [sp, #968]
	str	x8, [sp, #144]
	str	x8, [sp, #936]
	str	x9, [sp, #928]
	str	x19, [sp]
	bl	_printf
	ldr	x8, [sp, #960]
Lloh8:
	adrp	x0, l___unnamed_3@PAGE
Lloh9:
	add	x0, x0, l___unnamed_3@PAGEOFF
	str	x8, [sp]
	bl	_printf
	ldrb	w8, [sp, #959]
Lloh10:
	adrp	x0, l___unnamed_4@PAGE
Lloh11:
	add	x0, x0, l___unnamed_4@PAGEOFF
	str	x8, [sp]
	bl	_printf
	ldr	x8, [sp, #928]
Lloh12:
	adrp	x0, l___unnamed_5@PAGE
Lloh13:
	add	x0, x0, l___unnamed_5@PAGEOFF
	ldr	x8, [x8]
	str	x8, [sp]
	bl	_printf
Lloh14:
	adrp	x0, l___unnamed_6@PAGE
Lloh15:
	add	x0, x0, l___unnamed_6@PAGEOFF
Lloh16:
	adrp	x8, l_s.2@PAGE
Lloh17:
	add	x8, x8, l_s.2@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w8, #15                         ; =0xf
Lloh18:
	adrp	x0, l___unnamed_7@PAGE
Lloh19:
	add	x0, x0, l___unnamed_7@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w8, #12                         ; =0xc
Lloh20:
	adrp	x0, l___unnamed_8@PAGE
Lloh21:
	add	x0, x0, l___unnamed_8@PAGEOFF
	str	x8, [sp]
	bl	_printf
Lloh22:
	adrp	x0, l___unnamed_9@PAGE
Lloh23:
	add	x0, x0, l___unnamed_9@PAGEOFF
	str	x19, [sp]
	bl	_printf
	mov	w8, #25                         ; =0x19
Lloh24:
	adrp	x0, l___unnamed_10@PAGE
Lloh25:
	add	x0, x0, l___unnamed_10@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w8, #4                          ; =0x4
Lloh26:
	adrp	x0, l___unnamed_11@PAGE
Lloh27:
	add	x0, x0, l___unnamed_11@PAGEOFF
	str	x8, [sp]
	bl	_printf
	fmov	d0, #2.00000000
	fmov	d1, #10.00000000
	bl	_pow
	fcvtzs	x8, d0
Lloh28:
	adrp	x0, l___unnamed_12@PAGE
Lloh29:
	add	x0, x0, l___unnamed_12@PAGEOFF
	str	x8, [sp]
	bl	_printf
Lloh30:
	adrp	x0, l___unnamed_13@PAGE
Lloh31:
	add	x0, x0, l___unnamed_13@PAGEOFF
Lloh32:
	adrp	x8, l_s.3@PAGE
Lloh33:
	add	x8, x8, l_s.3@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	x8, #34079                      ; =0x851f
	mov	x10, #49808                     ; =0xc290
	mov	x9, #4612811918334230528        ; =0x4004000000000000
	movk	x8, #20971, lsl #16
	movk	x10, #10485, lsl #16
Lloh34:
	adrp	x0, l___unnamed_14@PAGE
Lloh35:
	add	x0, x0, l___unnamed_14@PAGEOFF
	movk	x8, #7864, lsl #32
	movk	x10, #36700, lsl #32
	movk	x8, #16393, lsl #48
	movk	x10, #16406, lsl #48
	stp	x9, x8, [sp, #88]
	str	x10, [sp, #80]
	str	x8, [sp]
	bl	_printf
	ldr	d0, [sp, #88]
Lloh36:
	adrp	x0, l___unnamed_15@PAGE
Lloh37:
	add	x0, x0, l___unnamed_15@PAGEOFF
	str	d0, [sp]
	bl	_printf
	ldr	d0, [sp, #80]
Lloh38:
	adrp	x0, l___unnamed_16@PAGE
Lloh39:
	add	x0, x0, l___unnamed_16@PAGEOFF
	str	d0, [sp]
	bl	_printf
Lloh40:
	adrp	x0, l___unnamed_17@PAGE
Lloh41:
	add	x0, x0, l___unnamed_17@PAGEOFF
Lloh42:
	adrp	x8, l_s.4@PAGE
Lloh43:
	add	x8, x8, l_s.4@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w8, #10                         ; =0xa
	mov	w9, #20                         ; =0x14
Lloh44:
	adrp	x10, l_s.5@PAGE
Lloh45:
	add	x10, x10, l_s.5@PAGEOFF
Lloh46:
	adrp	x0, l___unnamed_18@PAGE
Lloh47:
	add	x0, x0, l___unnamed_18@PAGEOFF
	stp	x8, x9, [sp, #56]
	str	x10, [sp, #72]
	stp	x8, x9, [sp, #32]
	str	x10, [sp, #48]
	str	x8, [sp]
	bl	_printf
	ldr	x8, [sp, #48]
Lloh48:
	adrp	x0, l___unnamed_19@PAGE
Lloh49:
	add	x0, x0, l___unnamed_19@PAGEOFF
	str	x8, [sp]
	bl	_printf
Lloh50:
	adrp	x0, l___unnamed_20@PAGE
Lloh51:
	add	x0, x0, l___unnamed_20@PAGEOFF
Lloh52:
	adrp	x8, l_s.6@PAGE
Lloh53:
	add	x8, x8, l_s.6@PAGEOFF
	str	x8, [sp]
	bl	_printf
Lloh54:
	adrp	x19, l_s.7@PAGE
Lloh55:
	add	x19, x19, l_s.7@PAGEOFF
Lloh56:
	adrp	x20, l_s.8@PAGE
Lloh57:
	add	x20, x20, l_s.8@PAGEOFF
	mov	x0, x19
	stp	x20, x19, [sp, #16]
	bl	_strlen
	mov	x21, x0
	mov	x0, x20
	bl	_strlen
	add	x8, x21, x0
	add	x0, x8, #1
	bl	_malloc
	mov	x1, x19
	mov	x21, x0
	bl	_strcpy
	mov	x0, x21
	mov	x1, x20
	bl	_strcat
Lloh58:
	adrp	x0, l___unnamed_21@PAGE
Lloh59:
	add	x0, x0, l___unnamed_21@PAGEOFF
	str	x21, [sp]
	bl	_printf
	ldp	x20, x19, [sp, #16]
	mov	x0, x19
	bl	_strlen
	mov	x21, x0
	mov	x0, x20
	bl	_strlen
	add	x8, x21, x0
	add	x0, x8, #1
	bl	_malloc
	mov	x1, x19
	mov	x21, x0
	bl	_strcpy
	mov	x0, x21
	mov	x1, x20
	bl	_strcat
Lloh60:
	adrp	x0, l___unnamed_22@PAGE
Lloh61:
	add	x0, x0, l___unnamed_22@PAGEOFF
	str	x21, [sp]
	bl	_printf
Lloh62:
	adrp	x0, l___unnamed_23@PAGE
Lloh63:
	add	x0, x0, l___unnamed_23@PAGEOFF
Lloh64:
	adrp	x8, l_s.9@PAGE
Lloh65:
	add	x8, x8, l_s.9@PAGEOFF
	str	x8, [sp]
	bl	_printf
	fmov	d0, #16.00000000
Lloh66:
	adrp	x0, l___unnamed_24@PAGE
Lloh67:
	add	x0, x0, l___unnamed_24@PAGEOFF
	fsqrt	d0, d0
	str	d0, [sp]
	bl	_printf
Lloh68:
	adrp	x0, l___unnamed_25@PAGE
Lloh69:
	add	x0, x0, l___unnamed_25@PAGEOFF
Lloh70:
	adrp	x8, l_s.10@PAGE
Lloh71:
	add	x8, x8, l_s.10@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	x0, #-99                        ; =0xffffffffffffff9d
	bl	_abs
	mov	x8, x0
Lloh72:
	adrp	x0, l___unnamed_26@PAGE
Lloh73:
	add	x0, x0, l___unnamed_26@PAGEOFF
	str	x8, [sp]
	bl	_printf
Lloh74:
	adrp	x0, l___unnamed_27@PAGE
Lloh75:
	add	x0, x0, l___unnamed_27@PAGEOFF
Lloh76:
	adrp	x8, l_s.11@PAGE
Lloh77:
	add	x8, x8, l_s.11@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w0, #5                          ; =0x5
	bl	_factorial
	mov	x8, x0
Lloh78:
	adrp	x0, l___unnamed_28@PAGE
Lloh79:
	add	x0, x0, l___unnamed_28@PAGEOFF
	str	x8, [sp]
	bl	_printf
Lloh80:
	adrp	x0, l___unnamed_29@PAGE
Lloh81:
	add	x0, x0, l___unnamed_29@PAGEOFF
Lloh82:
	adrp	x8, l_s.12@PAGE
Lloh83:
	add	x8, x8, l_s.12@PAGEOFF
	str	x8, [sp]
	bl	_printf
Lloh84:
	adrp	x0, l_s.13@PAGE
Lloh85:
	add	x0, x0, l_s.13@PAGEOFF
Lloh86:
	adrp	x1, l___unnamed_30@PAGE
Lloh87:
	add	x1, x1, l___unnamed_30@PAGEOFF
	bl	_fopen
Lloh88:
	adrp	x20, l_s.14@PAGE
Lloh89:
	add	x20, x20, l_s.14@PAGEOFF
	mov	x19, x0
	mov	x0, x20
	bl	_strlen
	mov	x2, x0
	mov	x0, x20
	mov	w1, #1                          ; =0x1
	mov	x3, x19
	bl	_fwrite
	mov	x0, x19
	bl	_fclose
Lloh90:
	adrp	x0, l_s.15@PAGE
Lloh91:
	add	x0, x0, l_s.15@PAGEOFF
Lloh92:
	adrp	x1, l___unnamed_31@PAGE
Lloh93:
	add	x1, x1, l___unnamed_31@PAGEOFF
	bl	_fopen
	mov	x19, x0
	mov	w0, #4096                       ; =0x1000
	bl	_malloc
	mov	w1, #1                          ; =0x1
	mov	w2, #4096                       ; =0x1000
	mov	x3, x19
	mov	x20, x0
	bl	_fread
	mov	x0, x19
	bl	_fclose
Lloh94:
	adrp	x0, l___unnamed_32@PAGE
Lloh95:
	add	x0, x0, l___unnamed_32@PAGEOFF
	str	x20, [sp]
	bl	_printf
Lloh96:
	adrp	x0, l___unnamed_33@PAGE
Lloh97:
	add	x0, x0, l___unnamed_33@PAGEOFF
Lloh98:
	adrp	x8, l_s.16@PAGE
Lloh99:
	add	x8, x8, l_s.16@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	x0, xzr
	add	sp, sp, #976
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp], #48             ; 16-byte Folded Reload
	ret
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
	.loh AdrpAdd	Lloh68, Lloh69
	.loh AdrpAdd	Lloh66, Lloh67
	.loh AdrpAdd	Lloh64, Lloh65
	.loh AdrpAdd	Lloh62, Lloh63
	.loh AdrpAdd	Lloh60, Lloh61
	.loh AdrpAdd	Lloh58, Lloh59
	.loh AdrpAdd	Lloh56, Lloh57
	.loh AdrpAdd	Lloh54, Lloh55
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
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_s:                                    ; @s
	.asciz	"=== 1. \353\263\200\354\210\230 ==="

l___unnamed_1:                          ; @0
	.asciz	"%s\n"

l_s.1:                                  ; @s.1
	.asciz	"Chaos"

l___unnamed_2:                          ; @1
	.asciz	"%d\n"

l___unnamed_3:                          ; @2
	.asciz	"%s\n"

l___unnamed_4:                          ; @3
	.asciz	"%d\n"

l___unnamed_5:                          ; @4
	.asciz	"%d\n"

l_s.2:                                  ; @s.2
	.asciz	"=== 2. \354\227\260\354\202\260 ==="

l___unnamed_6:                          ; @5
	.asciz	"%s\n"

l___unnamed_7:                          ; @6
	.asciz	"%d\n"

l___unnamed_8:                          ; @7
	.asciz	"%d\n"

l___unnamed_9:                          ; @8
	.asciz	"%d\n"

l___unnamed_10:                         ; @9
	.asciz	"%d\n"

l___unnamed_11:                         ; @10
	.asciz	"%d\n"

l___unnamed_12:                         ; @11
	.asciz	"%d\n"

l_s.3:                                  ; @s.3
	.asciz	"=== 3. \354\213\244\354\210\230 ==="

l___unnamed_13:                         ; @12
	.asciz	"%s\n"

l___unnamed_14:                         ; @13
	.asciz	"%g\n"

l___unnamed_15:                         ; @14
	.asciz	"%g\n"

l___unnamed_16:                         ; @15
	.asciz	"%g\n"

l_s.4:                                  ; @s.4
	.asciz	"=== 4. \352\265\254\354\241\260\354\262\264 ==="

l___unnamed_17:                         ; @16
	.asciz	"%s\n"

l_s.5:                                  ; @s.5
	.asciz	"Home"

l___unnamed_18:                         ; @17
	.asciz	"%d\n"

l___unnamed_19:                         ; @18
	.asciz	"%s\n"

l_s.6:                                  ; @s.6
	.asciz	"=== 5. concat ==="

l___unnamed_20:                         ; @19
	.asciz	"%s\n"

l_s.7:                                  ; @s.7
	.asciz	"Hello "

l_s.8:                                  ; @s.8
	.asciz	"World"

l___unnamed_21:                         ; @20
	.asciz	"%s\n"

l___unnamed_22:                         ; @21
	.asciz	"%s\n"

l_s.9:                                  ; @s.9
	.asciz	"=== 6. sqrt ==="

l___unnamed_23:                         ; @22
	.asciz	"%s\n"

l___unnamed_24:                         ; @23
	.asciz	"%g\n"

l_s.10:                                 ; @s.10
	.asciz	"=== 7. abs ==="

l___unnamed_25:                         ; @24
	.asciz	"%s\n"

l___unnamed_26:                         ; @25
	.asciz	"%d\n"

l_s.11:                                 ; @s.11
	.asciz	"=== 8. factorial ==="

l___unnamed_27:                         ; @26
	.asciz	"%s\n"

l___unnamed_28:                         ; @27
	.asciz	"%d\n"

l_s.12:                                 ; @s.12
	.asciz	"=== 9. \355\214\214\354\235\274 I/O ==="

l___unnamed_29:                         ; @28
	.asciz	"%s\n"

l_s.13:                                 ; @s.13
	.asciz	"all100.txt"

l_s.14:                                 ; @s.14
	.asciz	"OK!"

l___unnamed_30:                         ; @29
	.asciz	"w"

l_s.15:                                 ; @s.15
	.asciz	"all100.txt"

l___unnamed_31:                         ; @30
	.asciz	"r"

l___unnamed_32:                         ; @31
	.asciz	"%s\n"

l_s.16:                                 ; @s.16
	.asciz	"=== \354\240\204\353\266\200 \354\231\204\353\243\214! ==="

l___unnamed_33:                         ; @32
	.asciz	"%s\n"

.subsections_via_symbols
