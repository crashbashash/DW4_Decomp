/* 0x002ef9a0 — FUN_002ef9a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c0a00(int);
int Memory_GetAllocatorBySelector(int);

void FUN_002ef9a0(void) {
    *(int *)0x586F48 = FUN_002c0a00(Memory_GetAllocatorBySelector(*(int *)0x587038));
}
