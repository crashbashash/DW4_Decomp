/* 0x002f8a20 — FUN_002f8a20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int Memory_GetAllocatorBySelector(int);

void FUN_002f8a20(void) {
    if (Memory_GetAllocatorBySelector(2) == 0) {
        Memory_GetAllocatorBySelector(0);
    }
}
