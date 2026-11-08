	.set	noreorder

	.globl	FUN_00126f24
	.ent	FUN_00126f24
FUN_00126f24:
	sltiu	$2,$6,16
	bnez	$2,$L2
	andi	$5,$5,0xff
	andi	$2,$4,0xf
	bnez	$2,$L2
	move	$7,$4
	dsll	$3,$5,0x8
	lui	$2,0x101
	ori	$2,$2,0x101
	dsll	$2,$2,0x10
	ori	$2,$2,0x101
	dsll	$2,$2,0x10
	ori	$2,$2,0x101
	daddu	$10,$3,$5
	lui	$3,0x8080
	ori	$3,$3,0x8080
	dsll	$3,$3,0x10
	ori	$3,$3,0x8080
	dsll	$3,$3,0x10
	ori	$3,$3,0x8080
	pcpyh	$8,$10
	pcpyld	$9,$8,$8
	move	$4,$2
	pcpyld	$8,$3,$3
$L10:
	lq	$2,0($7)
	pxor	$2,$2,$9
	pcpyld	$10,$4,$4
	pnor	$3,$0,$2
	psubb	$2,$2,$10
	pand	$2,$2,$3
	pand	$2,$2,$8
	pcpyud	$3,$2,$9
	or	$2,$2,$3
	bnezl	$2,$L2
	move	$4,$7
	addiu	$6,$6,-16
	sltiu	$2,$6,16
	beqz	$2,$L10
	addiu	$7,$7,16
	move	$4,$7
$L2:
	lui	$2,0xffff
	addiu	$6,$6,-1
	ori	$2,$2,0xffff
	beq	$6,$2,$L20
	nop
	lui	$3,0xffff
	ori	$3,$3,0xffff
$L21:
	lbu	$2,0($4)
	beq	$2,$5,$L31
	addiu	$6,$6,-1
	bne	$6,$3,$L21
	addiu	$4,$4,1
$L20:
	jr	$31
	move	$2,$0
$L31:
	jr	$31
	move	$2,$4
	.end	FUN_00126f24

	.set	reorder
