/* 0x001d94f0 — FUN_001d94f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001d94f0(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 8);
}
