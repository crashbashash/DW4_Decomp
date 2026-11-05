/* 0x0027d920 — FUN_0027d920. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00273820();
extern int DAT_005707c0[4];
void FUN_0027d920(int arg0) {
    DAT_005707c0[0] = arg0;
    FUN_00273820(0x25, &DAT_005707c0[0], 1, 0, 0);
}
