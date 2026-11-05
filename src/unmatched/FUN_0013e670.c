/* 0x0013e670 — FUN_0013e670. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0016d170(int, int *);

void FUN_0013e670(void *arg0, int arg1) {
    int sp1C;

    sp1C = *(int *)((char *)arg0 + 12);
    FUN_0016d170(arg1, &sp1C);
}
