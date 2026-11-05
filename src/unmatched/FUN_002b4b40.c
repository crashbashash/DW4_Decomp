/* 0x002b4b40 — FUN_002b4b40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_002b4b40(void *arg0, float *arg1, float *arg2) {
    *arg1 = *(float *)((char *)(arg0) + 60);
    *arg2 = *(float *)((char *)(arg0) + 64);
}
