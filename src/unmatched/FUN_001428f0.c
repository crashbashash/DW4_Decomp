/* 0x001428f0 — FUN_001428f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001428f0(void *arg0) {
    *(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 8) = 0;
}
