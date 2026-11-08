	.set	noreorder

	.globl	FUN_0012a1e8
	.ent	FUN_0012a1e8
FUN_0012a1e8:
	addiu	$29,$29,-32
	sq	$16,0($29)
	move	$16,$4
	andi	$2,$16,0x7
	bnez	$2,$L15
	sq	$31,16($29)
	andi	$2,$16,0xf
	lui	$3,0x101
	ori	$3,$3,0x101
	dsll	$3,$3,0x10
	ori	$3,$3,0x101
	dsll	$3,$3,0x10
	ori	$3,$3,0x101
	lui	$4,0x8080
	ori	$4,$4,0x8080
	dsll	$4,$4,0x10
	ori	$4,$4,0x8080
	dsll	$4,$4,0x10
	ori	$4,$4,0x8080
	bnez	$2,$L3
	ld	$6,0($16)
	lq	$2,0($16)
	pcpyld	$7,$3,$3
	pcpyld	$8,$4,$4
	psubb	$3,$2,$7
	pnor	$2,$0,$2
	pand	$3,$3,$2
	pand	$3,$3,$8
	pcpyud	$2,$3,$3
	or	$3,$2,$3
	bnez	$3,$L15
	move	$4,$16
	addiu	$6,$4,16
$L14:
	lq	$2,0($6)
	pnor	$3,$0,$2
	psubb	$2,$2,$7
	pand	$2,$2,$3
	pand	$2,$2,$8
	pcpyud	$3,$2,$2
	or	$2,$2,$3
	beqzl	$2,$L14
	addiu	$6,$6,16
	b	$L15
	move	$4,$6
$L3:
	move	$7,$3
	move	$8,$4
	dsubu	$3,$6,$3
	nor	$2,$0,$6
	and	$3,$3,$2
	and	$3,$3,$4
	bnez	$3,$L15
	move	$4,$16
	addiu	$6,$16,8
$L16:
	ld	$2,0($6)
	nor	$3,$0,$2
	dsubu	$2,$2,$7
	and	$2,$2,$3
	and	$2,$2,$8
	beqzl	$2,$L16
	addiu	$6,$6,8
	move	$4,$6
$L15:
$L9:
	lb	$2,0($4)
	nop
	nop
	nop
	nop
	bnezl	$2,$L15
	addiu	$4,$4,1
	jal	strcpy
	nop
	move	$2,$16
	lq	$31,16($29)
	lq	$16,0($29)
	jr	$31
	addiu	$29,$29,32
	.end	FUN_0012a1e8

	.set	reorder
