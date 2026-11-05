/* 0x00266228 — FUN_00266228. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025b998();
int FUN_0025bb80();

void FUN_00266228(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 56) = arg1;
    FUN_0025bb80(*(int *)((char *)(arg0) + 4));
    FUN_0025b998(*(int *)((char *)(arg0) + 4), arg1);
}
