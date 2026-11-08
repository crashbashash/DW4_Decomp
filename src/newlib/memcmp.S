	.set	noreorder

	.globl	memcmp
	.ent	memcmp
memcmp:
	sltiu	$2,$6,16
	bnez	$2,$L2
	or	$2,$4,$5
	andi	$2,$2,0xf
	bnez	$2,$L2
	nop
$L5:
	lq	$3,0($4)
	sltiu	$7,$6,32
	lq	$2,0($5)
	addiu	$4,$4,16
	pxor	$8,$2,$3
	addiu	$2,$5,16
	pcpyud	$10,$8,$7
	or	$9,$10,$8
	movz	$5,$2,$9
	bnezl	$9,$L2
	addiu	$4,$4,-16
	beqz	$7,$L5
	addiu	$6,$6,-16
$L2:
	lui	$2,0xffff
	addiu	$6,$6,-1
	ori	$2,$2,0xffff
	beq	$6,$2,$L9
	nop
	lui	$7,0xffff
	ori	$7,$7,0xffff
$L10:
	lbu	$3,0($4)
	lbu	$2,0($5)
	beq	$3,$2,$L11
	addiu	$4,$4,1
	jr	$31
	subu	$2,$3,$2
$L11:
	addiu	$6,$6,-1
	bne	$6,$7,$L10
	addiu	$5,$5,1
$L9:
	jr	$31
	move	$2,$0
	.end	memcmp

	.set	reorder
