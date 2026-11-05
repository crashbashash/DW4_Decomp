/* 0x002eb210 — FUN_002eb210. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002eb210(void *arg0) {
    return *(int *)((char *)arg0 + 8) != 0;
}
