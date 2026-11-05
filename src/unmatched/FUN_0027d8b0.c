/* 0x0027d8b0 — FUN_0027d8b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00273820();
extern int DAT_00570780[4];
extern int DAT_005707c0[4];
extern int DAT_005708c0[4];
int *FUN_0027d8b0(int arg0) {
    DAT_005707c0[0] = arg0;
    FUN_00273820(0x24, &DAT_005707c0[0], 1, &DAT_005708c0[0], 4);
    *(int *)((char *)&(DAT_00570780[0]) + 0) = (int)((int) *(int *)((char *)&(DAT_005708c0[0]) + 0));
    *(int *)((char *)&(DAT_00570780[0]) + 4) = (int)((int) *(int *)((char *)&(DAT_005708c0[0]) + 4));
    *(int *)((char *)&(DAT_00570780[0]) + 8) = (int)((int) *(int *)((char *)&(DAT_005708c0[0]) + 8));
    *(int *)((char *)&(DAT_00570780[0]) + 12) = (int)((int) *(int *)((char *)&(DAT_005708c0[0]) + 12));
    return &DAT_00570780[0];
}
