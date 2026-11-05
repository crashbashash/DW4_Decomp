/* 0x002b18e0 — FUN_002b18e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002b18e0(void *arg0, int arg1, int arg2) {
    *(int *)((char *)arg0 + 8) = arg2;
    *(int *)((char *)arg0 + 0) = arg1;
    *(int *)((char *)arg0 + 4) = 0;
}
