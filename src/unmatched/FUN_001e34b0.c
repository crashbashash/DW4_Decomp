/* 0x001e34b0 — FUN_001e34b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
unsigned char FUN_001e34b0(void *arg0) {
    return *(int *)((char *)(arg0) + 81);
}
