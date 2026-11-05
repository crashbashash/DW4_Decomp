/* 0x00187520 — FUN_00187520. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001873c0();
extern int DAT_00560f40[4];
int FUN_00187520(void) {
    if (DAT_00560f40[0] == 0) {
        FUN_001873c0();
    }
    return DAT_00560f40[0];
}
