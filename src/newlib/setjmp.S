/* setjmp and longjmp for the R5900: the general registers are 128 bits wide, so each callee-saved
   register takes a quadword of the jmp_buf, followed by the callee-saved floating-point registers. */

	.set	noreorder

/* int setjmp (jmp_buf);  */
	.globl	setjmp
	.ent	setjmp
setjmp:
	.frame	$sp,0,$31

	sq	$16,0($4)	/* $s0 */
	sq	$17,16($4)	/* $s1 */
	sq	$18,32($4)	/* $s2 */
	sq	$19,48($4)	/* $s3 */
	sq	$20,64($4)	/* $s4 */
	sq	$21,80($4)	/* $s5 */
	sq	$22,96($4)	/* $s6 */
	sq	$23,112($4)	/* $s7 */
	sq	$30,128($4)	/* $s8 */

	swc1	$f24,144($4)
	swc1	$f25,148($4)
	swc1	$f26,152($4)
	swc1	$f27,156($4)
	swc1	$f28,160($4)
	swc1	$f29,164($4)
	swc1	$f30,168($4)
	swc1	$f31,172($4)

	sq	$sp,176($4)
	sq	$31,192($4)

	move	$2,$0

	j	$31
	nop

	.end	setjmp

/* volatile void longjmp (jmp_buf, int);  */
	.globl	longjmp
	.ent	longjmp
longjmp:
	.frame	$sp,0,$31

	lq	$16,0($4)	/* $s0 */
	lq	$17,16($4)	/* $s1 */
	lq	$18,32($4)	/* $s2 */
	lq	$19,48($4)	/* $s3 */
	lq	$20,64($4)	/* $s4 */
	lq	$21,80($4)	/* $s5 */
	lq	$22,96($4)	/* $s6 */
	lq	$23,112($4)	/* $s7 */
	lq	$30,128($4)	/* $s8 */

	lwc1	$f24,144($4)
	lwc1	$f25,148($4)
	lwc1	$f26,152($4)
	lwc1	$f27,156($4)
	lwc1	$f28,160($4)
	lwc1	$f29,164($4)
	lwc1	$f30,168($4)
	lwc1	$f31,172($4)

	lq	$sp,176($4)
	lq	$31,192($4)

	bne	$5,$0,1f
	nop
	li	$5,1
1:
	move	$2,$5

	j	$31
	nop

	.end	longjmp

	.set	reorder
