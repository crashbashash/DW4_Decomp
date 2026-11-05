/* 0x00187260 — FUN_00187260. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001870f0();
extern int DAT_00560f30[4];
int FUN_00187260(void) {
    if (DAT_00560f30[0] == 0) {
        FUN_001870f0();
    }
    return DAT_00560f30[0];
}
