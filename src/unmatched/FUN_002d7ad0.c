/* 0x002d7ad0 — FUN_002d7ad0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002d7ad0(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 24) = arg1;
}
