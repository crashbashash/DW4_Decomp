/* 0x001bb200 — FUN_001bb200. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0019a6e0(int);
int Memory_GetAllocatorBySelector(int);

void FUN_001bb200(void) {
    *(int *)0x562648 = FUN_0019a6e0(Memory_GetAllocatorBySelector(*(int *)0x587038));
}
