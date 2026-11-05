/* 0x001418c0 — FUN_001418c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001418c0(void *arg0, void *arg1) {
    *(long long *)((char *)(arg1) + 96) = (long long) *(long long *)((char *)(arg0) + 16);
}
