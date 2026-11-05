/* 0x00187b10 — FUN_00187b10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001879b0();
extern int DAT_00560f78[4];
int FUN_00187b10(void) {
    if (DAT_00560f78[0] == 0) {
        FUN_001879b0();
    }
    return DAT_00560f78[0];
}
