/* 0x00263450 — FUN_00263450. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002632c0();
extern int DAT_0049c8d8[4];
void FUN_00263450(void) {
    DAT_0049c8d8[0] = 0;
    FUN_002632c0();
}
