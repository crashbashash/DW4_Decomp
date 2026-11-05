/* 0x001e96d0 — FUN_001e96d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_0048dce0[4];
extern int DAT_0048dce8[4];
extern int DAT_00491478[4];
void FUN_001e96d0(int arg0, int arg1) {
    if ((DAT_0048dce0[0] != arg0) || (DAT_0048dce8[0] != arg1)) {
        DAT_00491478[0] |= 0x81;
    }
    DAT_0048dce0[0] = arg0;
    DAT_0048dce8[0] = arg1;
}
