/* 0x00448f00 — FUN_00448f00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00448f00(void *arg0, int arg1) {
    *(int *)((char *)arg0 + 12) = arg1;
    *(int *)((char *)arg0 + 8) = 6;
}
