/* 0x002607c0 — FUN_002607c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027e8a0();
extern int DAT_00499cd8[4];
extern int DAT_00499cdc[4];
void FUN_002607c0(int arg0, int arg1) {
    DAT_00499cd8[0] = arg0;
    DAT_00499cdc[0] = arg1;
    FUN_0027e8a0();
}
