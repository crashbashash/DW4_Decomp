/* 0x002777d0 — FUN_002777d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004abb48[4];
extern int DAT_004abb4c[4];
void FUN_002777d0(int arg0, int arg1) {
    if (arg0 == 0) {
        DAT_004abb48[0] = 0;
        DAT_004abb4c[0] = 0;
        return;
    }
    DAT_004abb48[0] = arg0;
    DAT_004abb4c[0] = arg1;
}
