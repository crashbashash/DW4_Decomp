/* 0x0027d780 — FUN_0027d780. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00273820();
extern int DAT_005707c0[4];
extern int DAT_005708c0[4];
int FUN_0027d780(int arg0, int arg1, int arg2) {
    *(int *)((char *)&(DAT_005707c0[0]) + 0) = arg0;
    *(int *)((char *)&(DAT_005707c0[0]) + 4) = arg1;
    *(int *)((char *)&(DAT_005707c0[0]) + 8) = arg2;
    FUN_00273820(0x20, &DAT_005707c0[0], 3, &DAT_005708c0[0], 1);
    return DAT_005708c0[0];
}
