/* The program's start-up file, after Sony's crt0.s: the _start point clears the registers and .bss, sets up the
 * main thread, the heap and the system, runs the static constructors, main and the static destructors, then
 * exits; _exit ends the program; _root is where the main thread returns, and exits it. Register copies are
 * spelled `or`: the original assembler encodes `move` that way, this one as `daddu`. */

	.set	noat
	.set	noreorder

	.text

	.globl	_start
	.ent	_start
_start:
/* clear the registers */
	padduw	$1, $0, $0
	padduw	$2, $0, $0
	padduw	$3, $0, $0
	padduw	$4, $0, $0
	padduw	$5, $0, $0
	padduw	$6, $0, $0
	padduw	$7, $0, $0
	padduw	$8, $0, $0
	padduw	$9, $0, $0
	padduw	$10, $0, $0
	padduw	$11, $0, $0
	padduw	$12, $0, $0
	padduw	$13, $0, $0
	padduw	$14, $0, $0
	padduw	$15, $0, $0
	padduw	$16, $0, $0
	padduw	$17, $0, $0
	padduw	$18, $0, $0
	padduw	$19, $0, $0
	padduw	$20, $0, $0
	padduw	$21, $0, $0
	padduw	$22, $0, $0
	padduw	$23, $0, $0
	padduw	$24, $0, $0
	padduw	$25, $0, $0
	padduw	$28, $0, $0
	padduw	$29, $0, $0
	padduw	$30, $0, $0
	padduw	$31, $0, $0
	mthi	$0
	mthi1	$0
	mtlo	$0
	mtlo1	$0
	mtsah	$0, 0
	mtc1	$0, $f0
	mtc1	$0, $f1
	mtc1	$0, $f2
	mtc1	$0, $f3
	mtc1	$0, $f4
	mtc1	$0, $f5
	mtc1	$0, $f6
	mtc1	$0, $f7
	mtc1	$0, $f8
	mtc1	$0, $f9
	mtc1	$0, $f10
	mtc1	$0, $f11
	mtc1	$0, $f12
	mtc1	$0, $f13
	mtc1	$0, $f14
	mtc1	$0, $f15
	mtc1	$0, $f16
	mtc1	$0, $f17
	mtc1	$0, $f18
	mtc1	$0, $f19
	mtc1	$0, $f20
	mtc1	$0, $f21
	mtc1	$0, $f22
	mtc1	$0, $f23
	mtc1	$0, $f24
	mtc1	$0, $f25
	mtc1	$0, $f26
	mtc1	$0, $f27
	mtc1	$0, $f28
	mtc1	$0, $f29
	mtc1	$0, $f30
	mtc1	$0, $f31
	adda.s	$f0, $f1
	sync.p
	ctc1	$0, $31

/* clear .bss: bytes up to a quadword boundary, quadwords, then the bytes left */
	lui	$2, %hi(_fbss)
	lui	$3, %hi(_end)
	addiu	$2, $2, %lo(_fbss)
	addiu	$3, $3, %lo(_end)
1:
	andi	$4, $2, 0xf
	beqz	$4, 2f
	nop
	sb	$0, ($2)
	addiu	$2, $2, 1
	nop
	j	1b
	nop
2:
	li	$4, 0xfffffff0
	and	$4, $3, $4
3:
	beq	$2, $4, 4f
	nop
	sq	$0, ($2)
	addiu	$2, $2, 16
	nop
	nop
	j	3b
	nop
4:
	beq	$2, $3, 5f
	nop
	sb	$0, ($2)
	addiu	$2, $2, 1
	nop
	nop
	j	4b
	nop
5:

/* initialize the main thread */
	lui	$4, %hi(_gp)
	lui	$5, %hi(_stack)
	lui	$6, %hi(_stack_size)
	lui	$7, %hi(_args)
	lui	$8, %hi(_root)
	addiu	$4, $4, %lo(_gp)
	addiu	$5, $5, %lo(_stack)
	addiu	$6, $6, %lo(_stack_size)
	addiu	$7, $7, %lo(_args)
	addiu	$8, $8, %lo(_root)
	or	$28, $4, $0
	addiu	$3, $0, 60		/* SetupThread */
	syscall
	or	$29, $2, $0

/* initialize the heap */
	lui	$4, %hi(_end)
	lui	$5, %hi(_heap_size)
	addiu	$4, $4, %lo(_end)
	addiu	$5, $5, %lo(_heap_size)
	addiu	$3, $0, 61		/* SetupHeap */
	syscall

/* initialize the system */
	jal	_InitSys
	nop

/* flush the data cache */
	jal	FlushCache
	or	$4, $0, $0

/* run the program */
	ei
	jal	__do_global_ctors
	nop
	lui	$2, %hi(_args)
	addiu	$2, $2, %lo(_args)
	lw	$4, ($2)
	jal	main
	addiu	$5, $2, 4
	jal	__do_global_dtors
	nop
	j	exit
	or	$4, $2, $0
	.end	_start

	.align	3
	.globl	_exit
	.ent	_exit
_exit:
	j	Exit
	nop
	.end	_exit

	.align	3
	.globl	_root
	.ent	_root
_root:
	addiu	$3, $0, 35		/* ExitThread */
	syscall
	.end	_root

