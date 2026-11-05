/* 0x001888e0 — FUN_001888e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00188780();
extern int DAT_00561008[4];
int FUN_001888e0(void) {
    if (DAT_00561008[0] == 0) {
        FUN_00188780();
    }
    return DAT_00561008[0];
}
