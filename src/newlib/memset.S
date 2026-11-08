	.set	noreorder

	.globl	memset
	.ent	memset
memset:
	sltiu	$2,$6,8
	bnez	$2,$L2
	move	$3,$4
	andi	$2,$4,0xf
	bnez	$2,$L2
	move	$7,$4
	andi	$9,$5,0xff
	sltiu	$10,$6,32
	move	$8,$9
	dsll	$3,$8,0x8
	or	$8,$3,$9
	pcpyh	$3,$8
	bnez	$10,$L31
	sltiu	$2,$6,8
	pcpyld	$8,$3,$3
$L12:
	sq	$8,0($7)
	addiu	$6,$6,-32
	addiu	$7,$7,16
	sltiu	$2,$6,32
	sq	$8,0($7)
	beqz	$2,$L12
	addiu	$7,$7,16
	b	$L31
	sltiu	$2,$6,8
$L16:
	addiu	$6,$6,-8
	addiu	$7,$7,8
	sltiu	$2,$6,8
$L31:
	nop
	nop
	beqzl	$2,$L16
	sd	$3,0($7)
	move	$3,$7
$L2:
	lui	$2,0xffff
	addiu	$6,$6,-1
	ori	$2,$2,0xffff
	beq	$6,$2,$L19
	nop
	lui	$2,0xffff
	ori	$2,$2,0xffff
$L20:
	sb	$5,0($3)
	addiu	$6,$6,-1
	addiu	$3,$3,1
	nop
	nop
	bne	$6,$2,$L20
	nop
$L19:
	jr	$31
	move	$2,$4
	.end	memset

	.set	reorder
