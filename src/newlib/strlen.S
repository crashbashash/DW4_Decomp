	.set	noreorder

	.globl	strlen
	.ent	strlen
strlen:
	andi	$2,$4,0x7
	bnez	$2,$L15
	move	$7,$4
	andi	$3,$4,0xf
	lui	$2,0x101
	ori	$2,$2,0x101
	dsll	$2,$2,0x10
	ori	$2,$2,0x101
	dsll	$2,$2,0x10
	ori	$2,$2,0x101
	bnez	$3,$L12
	move	$5,$4
	lq	$3,0($5)
	pcpyld	$8,$2,$2
	lui	$4,0x8080
	ori	$4,$4,0x8080
	dsll	$4,$4,0x10
	ori	$4,$4,0x8080
	dsll	$4,$4,0x10
	ori	$4,$4,0x8080
	psubb	$2,$3,$8
	pnor	$3,$0,$3
	pcpyld	$9,$4,$4
	pand	$2,$2,$3
	pand	$2,$2,$9
	pcpyud	$3,$2,$8
	or	$6,$3,$2
	bnezl	$6,$L15
	move	$4,$5
	addiu	$5,$5,16
$L14:
	lq	$2,0($5)
	pnor	$3,$0,$2
	psubb	$2,$2,$8
	pand	$2,$2,$3
	pand	$4,$2,$9
	pcpyud	$3,$4,$6
	or	$3,$3,$4
	beqzl	$3,$L14
	addiu	$5,$5,16
	b	$L15
	move	$4,$5
$L12:
	ld	$3,0($5)
	lui	$4,0x8080
	ori	$4,$4,0x8080
	dsll	$4,$4,0x10
	ori	$4,$4,0x8080
	dsll	$4,$4,0x10
	ori	$4,$4,0x8080
	dsubu	$2,$3,$2
	nor	$3,$0,$3
	and	$2,$2,$3
	and	$2,$2,$4
	bnezl	$2,$L15
	move	$4,$5
	lui	$6,0x101
	ori	$6,$6,0x101
	dsll	$6,$6,0x10
	ori	$6,$6,0x101
	dsll	$6,$6,0x10
	ori	$6,$6,0x101
	addiu	$5,$5,8
$L16:
	ld	$2,0($5)
	nor	$3,$0,$2
	dsubu	$2,$2,$6
	and	$2,$2,$3
	and	$2,$2,$4
	beqzl	$2,$L16
	addiu	$5,$5,8
	move	$4,$5
$L15:
$L9:
	lb	$2,0($4)
	nop
	nop
	nop
	nop
	bnezl	$2,$L15
	addiu	$4,$4,1
	jr	$31
	subu	$2,$4,$7
	.end	strlen

	.set	reorder
