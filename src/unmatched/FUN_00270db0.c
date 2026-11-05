/* 0x00270db0 — FUN_00270db0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004a927c[4];
extern int DAT_004a9280[4];
void FUN_00270db0(int arg0, int arg1) {
    if (arg0 == 0) {
        DAT_004a927c[0] = 0;
        DAT_004a9280[0] = 0;
        return;
    }
    DAT_004a927c[0] = arg0;
    DAT_004a9280[0] = arg1;
}
