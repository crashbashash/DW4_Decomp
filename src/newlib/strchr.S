	.set	noreorder

	.globl	FUN_0012a314
	.ent	FUN_0012a314
FUN_0012a314:
	andi	$2,$4,0x7
	bnez	$2,$L24
	andi	$5,$5,0xff
	dsll	$3,$5,0x8
	lui	$6,0x101
	ori	$6,$6,0x101
	dsll	$6,$6,0x10
	ori	$6,$6,0x101
	dsll	$6,$6,0x10
	ori	$6,$6,0x101
	daddu	$10,$3,$5
	andi	$3,$4,0xf
	dsll	$2,$10,0x10
	lui	$8,0x8080
	ori	$8,$8,0x8080
	dsll	$8,$8,0x10
	ori	$8,$8,0x8080
	dsll	$8,$8,0x10
	ori	$8,$8,0x8080
	daddu	$2,$2,$10
	dsll32	$10,$2,0x0
	bnez	$3,$L6
	daddu	$7,$2,$10
$L16:
	lq	$9,0($4)
	pcpyld	$10,$6,$6
	pnor	$3,$0,$9
	psubb	$2,$9,$10
	pcpyld	$6,$8,$8
	pand	$2,$2,$3
	pcpyld	$8,$7,$7
	pand	$2,$2,$6
	pcpyud	$3,$2,$7
	or	$3,$2,$3
	bnezl	$3,$L25
	lbu	$2,0($4)
	pxor	$2,$9,$8
	psubb	$3,$2,$10
	pnor	$2,$0,$2
	lui	$8,0x8080
	ori	$8,$8,0x8080
	dsll	$8,$8,0x10
	ori	$8,$8,0x8080
	dsll	$8,$8,0x10
	ori	$8,$8,0x8080
	pand	$3,$3,$2
	pand	$3,$3,$6
	lui	$6,0x101
	ori	$6,$6,0x101
	dsll	$6,$6,0x10
	ori	$6,$6,0x101
	dsll	$6,$6,0x10
	ori	$6,$6,0x101
	pcpyud	$2,$3,$5
	or	$3,$2,$3
	beqzl	$3,$L16
	addiu	$4,$4,16
	b	$L25
	lbu	$2,0($4)
$L6:
	ld	$9,0($4)
	nor	$3,$0,$9
	dsubu	$2,$9,$6
	and	$2,$2,$3
	and	$2,$2,$8
	bnezl	$2,$L25
	lbu	$2,0($4)
	xor	$2,$9,$7
	dsubu	$3,$2,$6
	nor	$2,$0,$2
	and	$3,$3,$2
	and	$3,$3,$8
	bnezl	$3,$L25
	lbu	$2,0($4)
	move	$9,$6
	addiu	$4,$4,8
$L26:
	ld	$6,0($4)
	dsubu	$2,$6,$9
	nor	$3,$0,$6
	and	$2,$2,$3
	and	$2,$2,$8
	bnez	$2,$L24
	xor	$2,$6,$7
	nor	$3,$0,$2
	dsubu	$2,$2,$9
	and	$2,$2,$3
	and	$2,$2,$8
	beqzl	$2,$L26
	addiu	$4,$4,8
	b	$L25
	lbu	$2,0($4)
$L17:
	beql	$2,$5,$L27
	lbu	$3,0($4)
	addiu	$4,$4,1
$L24:
	lbu	$2,0($4)
$L25:
	bnez	$2,$L17
	nop
	lbu	$3,0($4)
$L27:
	move	$2,$0
	xor	$3,$3,$5
	jr	$31
	movz	$2,$4,$3
	.end	FUN_0012a314

	.set	reorder
