	.set	noreorder

	.globl	FUN_0012aba0
	.ent	FUN_0012aba0
FUN_0012aba0:
	bnez	$6,$L3
	or	$3,$4,$5
$L20:
	jr	$31
	move	$2,$0
$L3:
	andi	$2,$3,0x7
	bnez	$2,$L22
	move	$2,$6
	andi	$2,$3,0xf
	sltiu	$7,$6,16
	lui	$9,0x101
	ori	$9,$9,0x101
	dsll	$9,$9,0x10
	ori	$9,$9,0x101
	dsll	$9,$9,0x10
	ori	$9,$9,0x101
	or	$2,$2,$7
	bnez	$2,$L31
	move	$7,$4
	lq	$3,0($4)
	pcpyld	$10,$9,$9
	lq	$2,0($5)
	lui	$8,0x8080
	ori	$8,$8,0x8080
	dsll	$8,$8,0x10
	ori	$8,$8,0x8080
	dsll	$8,$8,0x10
	ori	$8,$8,0x8080
	psubw	$3,$3,$2
	pcpyld	$9,$8,$8
	pcpyud	$2,$3,$4
	move	$8,$5
	or	$3,$2,$3
	bnez	$3,$L22
	move	$2,$6
	addiu	$6,$6,-16
$L34:
	beqz	$6,$L20
	nop
	lq	$2,0($7)
	pnor	$3,$0,$2
	psubb	$2,$2,$10
	pand	$2,$2,$3
	pand	$3,$2,$9
	pcpyud	$2,$3,$4
	or	$2,$2,$3
	bnez	$2,$L20
	addiu	$7,$7,16
	sltiu	$2,$6,16
	lq	$3,0($7)
	bnez	$2,$L6
	addiu	$8,$8,16
	lq	$2,0($8)
	psubw	$3,$3,$2
	pcpyud	$2,$3,$4
	or	$2,$2,$3
	beqzl	$2,$L34
	addiu	$6,$6,-16
	b	$L23
	move	$4,$7
$L31:
	sltiu	$2,$6,8
	bnez	$2,$L6
	move	$8,$5
	ld	$3,0($4)
	ld	$2,0($5)
	bne	$3,$2,$L22
	move	$2,$6
	addiu	$6,$6,-8
	lui	$10,0x8080
	ori	$10,$10,0x8080
	dsll	$10,$10,0x10
	ori	$10,$10,0x8080
	dsll	$10,$10,0x10
	ori	$10,$10,0x8080
$L24:
	beqz	$6,$L20
	nop
	ld	$2,0($7)
	nor	$3,$0,$2
	dsubu	$2,$2,$9
	and	$2,$2,$3
	and	$2,$2,$10
	bnez	$2,$L20
	addiu	$7,$7,8
	sltiu	$2,$6,8
	bnez	$2,$L6
	addiu	$8,$8,8
	ld	$3,0($7)
	ld	$2,0($8)
	beql	$3,$2,$L24
	addiu	$6,$6,-8
$L6:
	move	$4,$7
$L23:
	move	$5,$8
	move	$2,$6
$L22:
	beqz	$2,$L13
	addiu	$6,$6,-1
	b	$L21
	lb	$3,0($4)
	nop
$L14:
	beqz	$6,$L20
	nop
	beqz	$7,$L20
	addiu	$4,$4,1
	addiu	$5,$5,1
	lb	$3,0($4)
	addiu	$6,$6,-1
$L21:
	lb	$2,0($5)
	beq	$3,$2,$L14
	lbu	$7,0($4)
$L13:
	lbu	$2,0($5)
	lbu	$3,0($4)
	jr	$31
	subu	$2,$3,$2
	.end	FUN_0012aba0

	.set	reorder
