/* The EE's kernel-mode exception entries: the TLB exception handler and the debug exception handler save every
 * register to the exception frame and return, through ERET, to a stub that runs the registered handler on the
 * handler stack; the stub of the TLB path then leaves through system call -84, `_kExitTLBHandler`, which restores
 * the registers and returns from the exception. The debug stub finishes in a BREAK.
 *
 * The frame is data of the image: EEREG holds the general registers at 16 bytes each and is the top of the
 * handler stack, which grows down from it; EERH0, EERH1, EERL0, EERL1 and EERSA follow, the saved HI, HI1, LO,
 * LO1 and SA, then EEEPC, the saved EPC. */

	.set	noat
	.set	noreorder

	.globl	_kTLBException
	.ent	_kTLBException
_kTLBException:
	lui	$26, %hi(EEREG)
	addiu	$26, $26, %lo(EEREG)
	sq	$1, 0x10($26)
	sq	$2, 0x20($26)
	sq	$3, 0x30($26)
	sq	$4, 0x40($26)
	sq	$5, 0x50($26)
	sq	$6, 0x60($26)
	sq	$7, 0x70($26)
	sq	$8, 0x80($26)
	sq	$9, 0x90($26)
	sq	$10, 0xa0($26)
	sq	$11, 0xb0($26)
	sq	$12, 0xc0($26)
	sq	$13, 0xd0($26)
	sq	$14, 0xe0($26)
	sq	$15, 0xf0($26)
	sq	$16, 0x100($26)
	sq	$17, 0x110($26)
	sq	$18, 0x120($26)
	sq	$19, 0x130($26)
	sq	$20, 0x140($26)
	sq	$21, 0x150($26)
	sq	$22, 0x160($26)
	sq	$23, 0x170($26)
	sq	$24, 0x180($26)
	sq	$25, 0x190($26)
	sq	$28, 0x1c0($26)
	sq	$29, 0x1d0($26)
	sq	$30, 0x1e0($26)
	sq	$31, 0x1f0($26)
	mfhi	$2
	lui	$1, %hi(EERH0)
	sd	$2, %lo(EERH0)($1)
	mfhi1	$2
	lui	$1, %hi(EERH1)
	sd	$2, %lo(EERH1)($1)
	mflo	$2
	lui	$1, %hi(EERL0)
	sd	$2, %lo(EERL0)($1)
	mflo1	$2
	lui	$1, %hi(EERL1)
	sd	$2, %lo(EERL1)($1)
	mfsa	$2
	lui	$1, %hi(EERSA)
	sd	$2, %lo(EERSA)($1)
	mfc0	$4, $12
	mfc0	$5, $13
	mfc0	$6, $14
	mfc0	$7, $8
	lui	$8, %hi(EEREG)
	addiu	$8, $8, %lo(EEREG)
	lui	$1, %hi(EEEPC)
	sw	$6, %lo(EEEPC)($1)
	lui	$1, %hi(.L_kTLBLaunch)
	addiu	$1, $1, %lo(.L_kTLBLaunch)
	mtc0	$1, $14
	sync.p
	mfc0	$1, $12
	li	$2, -2
	and	$1, $1, $2
	mtc0	$1, $12
	sync.p
	eret
.L_kTLBLaunch:
	lui	$1, %hi(_kTLBRefillHandler)
	lw	$1, %lo(_kTLBRefillHandler)($1)
	lui	$29, %hi(EEREG)
	jalr	$1
	addiu	$29, $29, %lo(EEREG)
	li	$3, -84
	syscall
	.end	_kTLBException

	.globl	_kExitTLBHandler
	.ent	_kExitTLBHandler
_kExitTLBHandler:
	mfc0	$1, $12
	li	$26, -28
	and	$1, $1, $26
	mtc0	$1, $12
	sync.p
	lui	$2, %hi(EEEPC)
	lw	$2, %lo(EEEPC)($2)
	mtc0	$2, $14
	sync.p
	lui	$2, %hi(EERH0)
	ld	$2, %lo(EERH0)($2)
	mthi	$2
	lui	$2, %hi(EERH1)
	ld	$2, %lo(EERH1)($2)
	mthi1	$2
	lui	$2, %hi(EERL0)
	ld	$2, %lo(EERL0)($2)
	mtlo	$2
	lui	$2, %hi(EERL1)
	ld	$2, %lo(EERL1)($2)
	mtlo1	$2
	lui	$2, %hi(EERSA)
	ld	$2, %lo(EERSA)($2)
	mtsa	$2
	sync.p
	lui	$26, %hi(EEREG)
	addiu	$26, $26, %lo(EEREG)
	lq	$1, 0x10($26)
	lq	$2, 0x20($26)
	lq	$3, 0x30($26)
	lq	$4, 0x40($26)
	lq	$5, 0x50($26)
	lq	$6, 0x60($26)
	lq	$7, 0x70($26)
	lq	$8, 0x80($26)
	lq	$9, 0x90($26)
	lq	$10, 0xa0($26)
	lq	$11, 0xb0($26)
	lq	$12, 0xc0($26)
	lq	$13, 0xd0($26)
	lq	$14, 0xe0($26)
	lq	$15, 0xf0($26)
	lq	$16, 0x100($26)
	lq	$17, 0x110($26)
	lq	$18, 0x120($26)
	lq	$19, 0x130($26)
	lq	$20, 0x140($26)
	lq	$21, 0x150($26)
	lq	$22, 0x160($26)
	lq	$23, 0x170($26)
	lq	$24, 0x180($26)
	lq	$25, 0x190($26)
	lq	$28, 0x1c0($26)
	lq	$29, 0x1d0($26)
	lq	$30, 0x1e0($26)
	lq	$31, 0x1f0($26)
	mfc0	$26, $12
	ori	$26, $26, 0x13
	mtc0	$26, $12
	sync.p
	eret
	.end	_kExitTLBHandler

	.globl	_kDebugException
	.ent	_kDebugException
_kDebugException:
	lui	$26, %hi(EEREG)
	addiu	$26, $26, %lo(EEREG)
	sq	$1, 0x10($26)
	sq	$2, 0x20($26)
	sq	$3, 0x30($26)
	sq	$4, 0x40($26)
	sq	$5, 0x50($26)
	sq	$6, 0x60($26)
	sq	$7, 0x70($26)
	sq	$8, 0x80($26)
	sq	$9, 0x90($26)
	sq	$10, 0xa0($26)
	sq	$11, 0xb0($26)
	sq	$12, 0xc0($26)
	sq	$13, 0xd0($26)
	sq	$14, 0xe0($26)
	sq	$15, 0xf0($26)
	sq	$16, 0x100($26)
	sq	$17, 0x110($26)
	sq	$18, 0x120($26)
	sq	$19, 0x130($26)
	sq	$20, 0x140($26)
	sq	$21, 0x150($26)
	sq	$22, 0x160($26)
	sq	$23, 0x170($26)
	sq	$24, 0x180($26)
	sq	$25, 0x190($26)
	sq	$28, 0x1c0($26)
	sq	$29, 0x1d0($26)
	sq	$30, 0x1e0($26)
	sq	$31, 0x1f0($26)
	mfhi	$2
	lui	$1, %hi(EERH0)
	sd	$2, %lo(EERH0)($1)
	mfhi1	$2
	lui	$1, %hi(EERH1)
	sd	$2, %lo(EERH1)($1)
	mflo	$2
	lui	$1, %hi(EERL0)
	sd	$2, %lo(EERL0)($1)
	mflo1	$2
	lui	$1, %hi(EERL1)
	sd	$2, %lo(EERL1)($1)
	mfsa	$2
	lui	$1, %hi(EERSA)
	sd	$2, %lo(EERSA)($1)
	mfc0	$4, $12
	mfc0	$5, $13
	mfc0	$6, $14
	mfc0	$7, $8
	mfc0	$8, $23
	lui	$9, %hi(EEREG)
	addiu	$9, $9, %lo(EEREG)
	lui	$1, %hi(.L_kDebugLaunch)
	addiu	$1, $1, %lo(.L_kDebugLaunch)
	mtc0	$1, $14
	sync.p
	mfc0	$1, $12
	li	$2, -2
	and	$1, $1, $2
	mtc0	$1, $12
	sync.p
	eret
.L_kDebugLaunch:
	andi	$2, $5, 0x7c
	lui	$1, %hi(_kDebugHandler)
	addu	$1, $1, $2
	lw	$1, %lo(_kDebugHandler)($1)
	lui	$29, %hi(EEREG)
	jalr	$1
	addiu	$29, $29, %lo(EEREG)
	break	0x3ff, 0x3ff
	nop
	.end	_kDebugException
