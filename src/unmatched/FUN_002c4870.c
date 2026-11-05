/* 0x002c4870 — FUN_002c4870. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c4710();
extern int DAT_00586380[4];
int FUN_002c4870(void) {
    if (DAT_00586380[0] == 0) {
        FUN_002c4710();
    }
    return DAT_00586380[0];
}
