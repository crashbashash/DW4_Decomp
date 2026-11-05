/* 0x00125f70 — FUN_00125f70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004d3e80[4];
int *FUN_00125f70(void) {
    return &DAT_004d3e80[0];
}
