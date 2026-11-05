/* 0x002cce00 — FUN_002cce00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ccca0();
extern int DAT_00586990[4];
int FUN_002cce00(void) {
    if (DAT_00586990[0] == 0) {
        FUN_002ccca0();
    }
    return DAT_00586990[0];
}
