/* 0x002d35c0 — FUN_002d35c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
unsigned short FUN_002d35c0(void *arg0) {
    return *(int *)((char *)(arg0) + 52);
}
