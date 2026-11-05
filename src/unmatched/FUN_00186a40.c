/* 0x00186a40 — FUN_00186a40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00186e40();
int FUN_00186f70();
int FUN_00190370();
extern unsigned char DAT_00554b7c[4];
void FUN_00186a40(void) {
    if (DAT_00554b7c[0] == 0) {
        DAT_00554b7c[0] = 1;
        FUN_00186e40();
        FUN_00186f70();
        FUN_00190370();
    }
}
