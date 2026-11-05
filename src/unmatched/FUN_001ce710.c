/* 0x001ce710 — FUN_001ce710. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0019a6e0(int);
int Memory_GetAllocatorBySelector(int);

void FUN_001ce710(void) {
    *(int *)0x562790 = FUN_0019a6e0(Memory_GetAllocatorBySelector(*(int *)0x587038));
}
