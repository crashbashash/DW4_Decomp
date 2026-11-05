/* 0x0030e430 — FUN_0030e430. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0030e430(int *arg0, void *arg1, int arg2) {
    *(int *)((char *)arg1 + 24) = arg2;
    *arg0 = *(int *)0x4FB410;
}
