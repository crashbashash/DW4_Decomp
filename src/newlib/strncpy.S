	.set	noreorder

	.globl	strncpy
	.ent	strncpy
strncpy:
	move	$8,$4
	or	$7,$5,$4
	li	$10,16
	andi	$2,$7,0x7
	li	$9,8
	bnez	$2,$L9
	andi	$2,$7,0xf
	movz	$9,$10,$2
	bnez	$2,$L17
	sltu	$2,$6,$9
	bnez	$2,$L9
	nop
	lui	$7,0x101
	ori	$7,$7,0x101
	dsll	$7,$7,0x10
	ori	$7,$7,0x101
	dsll	$7,$7,0x10
	ori	$7,$7,0x101
	lq	$3,0($5)
	pcpyld	$9,$7,$7
	pnor	$3,$0,$3
	lui	$7,0x8080
	ori	$7,$7,0x8080
	dsll	$7,$7,0x10
	ori	$7,$7,0x8080
	dsll	$7,$7,0x10
	ori	$7,$7,0x8080
	psubb	$2,$3,$9
	pcpyld	$10,$7,$7
	pand	$2,$2,$3
	pand	$2,$2,$10
	pcpyud	$3,$2,$4
	or	$3,$2,$3
	bnez	$3,$L5
	move	$7,$8
	lq	$3,0($5)
	addiu	$6,$6,-16
	addiu	$5,$5,16
	sltiu	$2,$6,16
	sq	$3,0($7)
	bnez	$2,$L5
	addiu	$7,$7,16
	lq	$2,0($5)
	pnor	$3,$0,$2
	psubb	$2,$2,$9
	pand	$2,$2,$3
	pand	$2,$2,$10
	pcpyud	$3,$2,$4
	or	$2,$2,$3
	beqzl	$2,$L19
	lq	$3,0($5)
	b	$L9
	move	$4,$7
$L17:
	bnez	$2,$L9
	nop
	ld	$3,0($5)
	lui	$9,0x101
	ori	$9,$9,0x101
	dsll	$9,$9,0x10
	ori	$9,$9,0x101
	dsll	$9,$9,0x10
	ori	$9,$9,0x101
	lui	$10,0x8080
	ori	$10,$10,0x8080
	dsll	$10,$10,0x10
	ori	$10,$10,0x8080
	dsll	$10,$10,0x10
	ori	$10,$10,0x8080
	dsubu	$2,$3,$9
	nor	$3,$0,$3
	and	$2,$2,$3
	and	$2,$2,$10
	bnez	$2,$L5
	move	$7,$8
	ld	$3,0($5)
	nop
$L19:
	addiu	$6,$6,-8
	addiu	$5,$5,8
	sltiu	$2,$6,8
	sd	$3,0($7)
	bnez	$2,$L5
	addiu	$7,$7,8
	ld	$2,0($5)
	nor	$3,$0,$2
	dsubu	$2,$2,$9
	and	$2,$2,$3
	and	$2,$2,$10
	beqzl	$2,$L19
	ld	$3,0($5)
$L5:
	move	$4,$7
$L9:
	beqz	$6,$L18
	move	$2,$6
	lbu	$2,0($5)
	addiu	$6,$6,-1
	addiu	$5,$5,1
	sb	$2,0($4)
	sll	$2,$2,0x18
	bnez	$2,$L9
	addiu	$4,$4,1
	move	$2,$6
	beqz	$2,$L18
	addiu	$6,$6,-1
$L16:
	sb	$0,0($4)
	move	$2,$6
	addiu	$4,$4,1
	addiu	$6,$6,-1
	nop
	bnez	$2,$L16
	nop
$L18:
	jr	$31
	move	$2,$8
	.end	strncpy

	.set	reorder
