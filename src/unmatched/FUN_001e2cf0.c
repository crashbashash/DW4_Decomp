/* 0x001e2cf0 — FUN_001e2cf0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001e2cf0(void *arg0) {
    *(int *)((char *)(arg0) + 40) = 1;
}
