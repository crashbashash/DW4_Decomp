	.set	noreorder

	.globl	igStrCmp
	.ent	igStrCmp
igStrCmp:
	or	$8,$4,$5
	andi	$2,$8,0x7
	bnezl	$2,$L19
	lb	$2,0($4)
	andi	$9,$8,0xf
	lui	$7,0x101
	ori	$7,$7,0x101
	dsll	$7,$7,0x10
	ori	$7,$7,0x101
	dsll	$7,$7,0x10
	ori	$7,$7,0x101
	lui	$6,0x8080
	ori	$6,$6,0x8080
	dsll	$6,$6,0x10
	ori	$6,$6,0x8080
	dsll	$6,$6,0x10
	ori	$6,$6,0x8080
	bnez	$9,$L18
	ld	$2,0($5)
	lq	$3,0($4)
	pcpyld	$8,$7,$7
	lq	$2,0($5)
	pcpyld	$10,$6,$6
	psubw	$7,$2,$3
	pcpyud	$6,$7,$4
	or	$3,$6,$7
	bnezl	$3,$L19
	lb	$2,0($4)
	lq	$2,0($4)
	pnor	$3,$0,$2
$L2:
	psubb	$2,$2,$8
	pand	$2,$2,$3
	pand	$2,$2,$10
	pcpyud	$3,$2,$4
	or	$6,$3,$2
	beqz	$6,$L5
	addiu	$4,$4,16
	jr	$31
	move	$2,$0
$L5:
	addiu	$5,$5,16
	lq	$2,0($4)
	lq	$3,0($5)
	psubw	$7,$2,$3
	pcpyud	$6,$7,$4
	or	$9,$6,$7
	beqzl	$9,$L2
	pnor	$3,$0,$2
	b	$L19
	lb	$2,0($4)
$L18:
	ld	$3,0($4)
	bnel	$3,$2,$L19
	lb	$2,0($4)
	ld	$2,0($4)
	nor	$8,$0,$2
$L21:
	dsubu	$2,$2,$7
	and	$2,$2,$8
	and	$2,$2,$6
	beqz	$2,$L6
	addiu	$4,$4,8
	jr	$31
	move	$2,$0
$L6:
	addiu	$5,$5,8
	ld	$2,0($4)
	ld	$3,0($5)
	beql	$3,$2,$L21
	nor	$8,$0,$2
	b	$L19
	lb	$2,0($4)
$L12:
	sll	$2,$3,0x18
	lb	$3,0($5)
	sra	$2,$2,0x18
	bnel	$2,$3,$L22
	lbu	$3,0($4)
	addiu	$4,$4,1
	addiu	$5,$5,1
	lb	$2,0($4)
$L19:
$L20:
	bnez	$2,$L12
	lbu	$3,0($4)
$L22:
	lbu	$2,0($5)
	jr	$31
	subu	$2,$3,$2
	.end	igStrCmp

	.set	reorder
