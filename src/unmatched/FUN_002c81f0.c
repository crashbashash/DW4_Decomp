/* 0x002c81f0 — FUN_002c81f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c8090();
extern int DAT_00586780[4];
int FUN_002c81f0(void) {
    if (DAT_00586780[0] == 0) {
        FUN_002c8090();
    }
    return DAT_00586780[0];
}
