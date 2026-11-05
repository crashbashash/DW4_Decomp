/* 0x00265878 — FUN_00265878. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002743c0();
int FUN_00276e30();
extern int DAT_004a52c0[4];
void FUN_00265878(int arg0) {
    DAT_004a52c0[0] = arg0;
    FUN_00276e30();
    FUN_002743c0(arg0);
}
