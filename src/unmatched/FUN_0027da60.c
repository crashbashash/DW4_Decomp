/* 0x0027da60 — FUN_0027da60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00273820();
extern int DAT_005707c0[4];
extern int DAT_005708c0[4];
int FUN_0027da60(int arg0, int arg1) {
    *(int *)((char *)&(DAT_005707c0[0]) + 0) = arg0;
    *(int *)((char *)&(DAT_005707c0[0]) + 4) = arg1;
    FUN_00273820(0x29, &DAT_005707c0[0], 2, &DAT_005708c0[0], 1);
    return DAT_005708c0[0];
}
