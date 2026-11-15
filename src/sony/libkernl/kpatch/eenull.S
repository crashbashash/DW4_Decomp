/* The user-mode side of an alarm callback. srcfile's kernel code copies this to 0x82000 and returns from the
 * alarm interrupt into it in user mode, with the handler in $3 and its arguments in $4..$6: it runs the handler on
 * the stack below 0x82000 and goes back to the kernel through system call -8. */

	.set	noat
	.set	noreorder

	.globl	UserModeDispatcher
	.ent	UserModeDispatcher
UserModeDispatcher:
	lui	$29, 0x0008
	jalr	$3
	addiu	$29, $29, 0x1fc0
	li	$3, -8
	syscall
	.end	UserModeDispatcher
	.p2align 4
