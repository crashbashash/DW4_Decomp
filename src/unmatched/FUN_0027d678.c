/* 0x0027d678 — FUN_0027d678. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027d568();

void FUN_0027d678(int arg0, void *arg1) {
    *(int *)((char *)(arg1) + 0) = (int)((int) (arg0 + 0x10));
    *(int *)((char *)(arg1) + 4) = FUN_0027d568(arg0 + 8);
}
