/* 0x00460f70 — FUN_00460f70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_0058c940[4];
int FUN_00460f70(void) {
    return DAT_0058c940[0];
}
