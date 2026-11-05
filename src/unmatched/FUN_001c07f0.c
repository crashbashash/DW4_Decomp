/* 0x001c07f0 — FUN_001c07f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001c07f0(void *arg0) {
    *(char *)((char *)(arg0) + 8) = 1;
    *(char *)((char *)(arg0) + 9) = 3;
    *(char *)((char *)(arg0) + 10) = 1;
}
