/* 0x002ae010 — FUN_002ae010. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002ae010(void *arg0, int arg1) {
    *(int *)((char *)arg0 + 0) = 0;
    *(int *)((char *)arg0 + 8) = arg1;
    *(int *)((char *)arg0 + 4) = 0;
}
