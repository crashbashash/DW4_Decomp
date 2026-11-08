	.set	noreorder

	.globl	FUN_0012a9f0
	.ent	FUN_0012a9f0
FUN_0012a9f0:
	move	$8,$4
	andi	$2,$8,0x7
	bnezl	$2,$L18
	lb	$2,0($4)
	andi	$3,$8,0xf
	bnezl	$3,$L17
	ld	$2,0($8)
	lui	$7,0x101
	ori	$7,$7,0x101
	dsll	$7,$7,0x10
	ori	$7,$7,0x101
	dsll	$7,$7,0x10
	ori	$7,$7,0x101
	lq	$2,0($8)
	pcpyld	$9,$7,$7
	lui	$4,0x8080
	ori	$4,$4,0x8080
	dsll	$4,$4,0x10
	ori	$4,$4,0x8080
	dsll	$4,$4,0x10
	ori	$4,$4,0x8080
	psubb	$3,$2,$9
	pnor	$2,$0,$2
	pcpyld	$10,$4,$4
	pand	$3,$3,$2
	pand	$3,$3,$10
	pcpyud	$2,$3,$4
	or	$3,$3,$2
	bnez	$3,$L5
	move	$7,$8
	addiu	$7,$7,16
	nop
$L39:
	lq	$2,0($7)
	pnor	$3,$0,$2
	psubb	$2,$2,$9
	pand	$2,$2,$3
	pand	$2,$2,$10
	pcpyud	$3,$2,$4
	or	$2,$2,$3
	beqz	$2,$L39
	addiu	$7,$7,16
	b	$L5
	addiu	$7,$7,-16
$L17:
	lui	$9,0x101
	ori	$9,$9,0x101
	dsll	$9,$9,0x10
	ori	$9,$9,0x101
	dsll	$9,$9,0x10
	ori	$9,$9,0x101
	lui	$4,0x8080
	ori	$4,$4,0x8080
	dsll	$4,$4,0x10
	ori	$4,$4,0x8080
	dsll	$4,$4,0x10
	ori	$4,$4,0x8080
	dsubu	$3,$2,$9
	nor	$2,$0,$2
	and	$3,$3,$2
	and	$3,$3,$4
	bnez	$3,$L5
	move	$7,$8
	addiu	$7,$7,8
$L19:
	ld	$2,0($7)
	nor	$3,$0,$2
	dsubu	$2,$2,$9
	and	$2,$2,$3
	and	$2,$2,$4
	beqzl	$2,$L19
	addiu	$7,$7,8
$L5:
	move	$4,$7
	lb	$2,0($4)
$L18:
	beqz	$2,$L9
	addiu	$6,$6,-1
	addiu	$4,$4,1
$L20:
	lb	$2,0($4)
	nop
	nop
	nop
	nop
	bnezl	$2,$L20
	addiu	$4,$4,1
$L9:
	lui	$2,0xffff
	ori	$2,$2,0xffff
	beq	$6,$2,$L13
	nop
	lbu	$2,0($5)
	addiu	$5,$5,1
	sb	$2,0($4)
	sll	$2,$2,0x18
	beqz	$2,$L13
	addiu	$4,$4,1
	lui	$3,0xffff
	ori	$3,$3,0xffff
	nop
$L14:
	beqzl	$6,$L12
	sb	$0,0($4)
$L12:
	addiu	$6,$6,-1
	beq	$6,$3,$L13
	nop
	lbu	$2,0($5)
	addiu	$5,$5,1
	sb	$2,0($4)
	sll	$2,$2,0x18
	bnez	$2,$L14
	addiu	$4,$4,1
$L13:
	jr	$31
	move	$2,$8
	.end	FUN_0012a9f0

	.set	reorder
