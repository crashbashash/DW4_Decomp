/* 0x002c1c70 — FUN_002c1c70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002c1b10();
extern int DAT_00586058[4];
int FUN_002c1c70(void) {
    if (DAT_00586058[0] == 0) {
        FUN_002c1b10();
    }
    return DAT_00586058[0];
}
