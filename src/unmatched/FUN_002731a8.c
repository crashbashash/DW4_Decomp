/* 0x002731a8 — FUN_002731a8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004aa3b0[];
int FUN_0010e2a8();
extern int DAT_0056e580[4];
extern int DAT_0056e680[4];
int FUN_002731a8(int arg0, int arg1, int arg2, int arg3) {
    *(int *)((char *)&(DAT_0056e580[0]) + 0) = arg0;
    *(int *)((char *)&(DAT_0056e580[0]) + 4) = arg1;
    *(int *)((char *)&(DAT_0056e580[0]) + 8) = arg2;
    *(int *)((char *)&(DAT_0056e580[0]) + 12) = arg3;
    FUN_0010e2a8(DAT_004aa3b0, 2, 0, &DAT_0056e580[0], 0x10, &DAT_0056e680[0], 4, 0, 0);
    return DAT_0056e680[0];
}
