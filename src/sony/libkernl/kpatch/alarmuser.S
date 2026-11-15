/* The kernel side of an alarm handler's trip through user mode. CallUserHandler keeps the interrupt's return
 * address and stack, puts the user-mode dispatcher in EPC and the handler and its arguments where the dispatcher
 * takes them ($3, then $4..$6), and returns from the exception into user mode. The dispatcher comes back through
 * system call 8, ReturnFromUserHandler, which drops back to kernel mode and returns to CallUserHandler's caller
 * on the kept stack. */

	.set	noat
	.set	noreorder

	.bss
	.align	4
savedRa:
	.space	16
savedSp:
	.space	16

	.text
	.align	5

	.globl	CallUserHandler
	.ent	CallUserHandler
CallUserHandler:
	lui	$26, %hi(savedRa)
	sw	$31, %lo(savedRa)($26)
	lui	$26, %hi(savedSp)
	sw	$29, %lo(savedSp)($26)
	mtc0	$4, $14
	sync.p
	move	$3, $5
	move	$4, $6
	move	$5, $7
	move	$6, $8
	/* user mode, with the exception level kept until ERET */
	mfc0	$26, $12
	ori	$26, $26, 0x12
	mtc0	$26, $12
	sync.p
	eret
	nop
	.end	CallUserHandler

	.globl	ReturnFromUserHandler
	.ent	ReturnFromUserHandler
ReturnFromUserHandler:
	/* kernel mode, exception level and interrupts off */
	mfc0	$1, $12
	li	$26, -28
	and	$1, $1, $26
	mtc0	$1, $12
	sync.p
	lui	$26, %hi(savedRa)
	lw	$31, %lo(savedRa)($26)
	lui	$26, %hi(savedSp)
	jr	$31
	lw	$29, %lo(savedSp)($26)
	.end	ReturnFromUserHandler
