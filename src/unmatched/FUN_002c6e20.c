/* 0x002c6e20 — FUN_002c6e20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c6cc0();
extern int DAT_00586640[4];
int FUN_002c6e20(void) {
    if (DAT_00586640[0] == 0) {
        FUN_002c6cc0();
    }
    return DAT_00586640[0];
}
