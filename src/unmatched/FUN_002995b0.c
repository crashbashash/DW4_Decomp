/* 0x002995b0 — FUN_002995b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002776c0();

void FUN_002995b0(void *arg0, int *arg1) {
    *arg1 = FUN_002776c0(*(int *)((char *)(arg0) + 76));
}
