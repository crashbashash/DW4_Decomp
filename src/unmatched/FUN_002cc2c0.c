/* 0x002cc2c0 — FUN_002cc2c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002cc160();
extern int DAT_00586938[4];
int FUN_002cc2c0(void) {
    if (DAT_00586938[0] == 0) {
        FUN_002cc160();
    }
    return DAT_00586938[0];
}
