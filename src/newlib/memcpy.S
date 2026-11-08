	.set	noreorder

	.globl	memcpy
	.ent	memcpy
memcpy:
	move	$8,$4
	sltiu	$2,$6,32
	bnez	$2,$L2
	move	$3,$8
	or	$2,$5,$8
	andi	$2,$2,0xf
	bnezl	$2,$L20
	addiu	$6,$6,-1
	move	$7,$8
$L5:
	lq	$3,0($5)
	addiu	$6,$6,-32
	addiu	$5,$5,16
	sltiu	$4,$6,32
	sq	$3,0($7)
	addiu	$7,$7,16
	lq	$2,0($5)
	addiu	$5,$5,16
	sq	$2,0($7)
	beqz	$4,$L5
	addiu	$7,$7,16
	sltiu	$2,$6,8
	bnez	$2,$L2
	move	$3,$7
$L9:
	ld	$3,0($5)
	addiu	$6,$6,-8
	addiu	$5,$5,8
	sltiu	$2,$6,8
	sd	$3,0($7)
	beqz	$2,$L9
	addiu	$7,$7,8
	move	$3,$7
$L2:
	addiu	$6,$6,-1
$L20:
	li	$2,-1
	beq	$6,$2,$L12
	move	$4,$2
$L13:
	lbu	$2,0($5)
	addiu	$6,$6,-1
	addiu	$5,$5,1
	sb	$2,0($3)
	addiu	$3,$3,1
	bne	$6,$4,$L13
	nop
$L12:
	jr	$31
	move	$2,$8
	.end	memcpy

	.set	reorder
