	.set	noreorder

	.globl	memmove
	.ent	memmove
memmove:
	move	$8,$4
	sltu	$2,$5,$8
	beqz	$2,$L2
	move	$3,$8
	addu	$7,$5,$6
	sltu	$2,$8,$7
	beqz	$2,$L2
	li	$2,-1
	addu	$3,$8,$6
	addiu	$6,$6,-1
	beq	$6,$2,$L7
	move	$5,$7
	move	$4,$2
$L5:
	addiu	$5,$5,-1
	addiu	$3,$3,-1
	lbu	$2,0($5)
	addiu	$6,$6,-1
	sb	$2,0($3)
	bne	$6,$4,$L5
	nop
	jr	$31
	move	$2,$8
$L2:
	sltiu	$2,$6,32
	bnezl	$2,$L29
	addiu	$6,$6,-1
	or	$2,$5,$3
	andi	$2,$2,0xf
	bnezl	$2,$L29
	addiu	$6,$6,-1
	move	$7,$3
$L11:
	lq	$3,0($5)
	addiu	$6,$6,-32
	addiu	$5,$5,16
	sltiu	$4,$6,32
	sq	$3,0($7)
	addiu	$7,$7,16
	lq	$2,0($5)
	addiu	$5,$5,16
	sq	$2,0($7)
	beqz	$4,$L11
	addiu	$7,$7,16
	sltiu	$2,$6,8
	bnez	$2,$L30
	move	$3,$7
$L15:
	ld	$3,0($5)
	addiu	$6,$6,-8
	addiu	$5,$5,8
	sltiu	$2,$6,8
	sd	$3,0($7)
	beqz	$2,$L15
	addiu	$7,$7,8
	move	$3,$7
$L30:
	addiu	$6,$6,-1
$L29:
	li	$2,-1
	beq	$6,$2,$L7
	move	$4,$2
$L19:
	lbu	$2,0($5)
	addiu	$6,$6,-1
	addiu	$5,$5,1
	sb	$2,0($3)
	addiu	$3,$3,1
	bne	$6,$4,$L19
	nop
$L7:
	jr	$31
	move	$2,$8
	.end	memmove

	.set	reorder
