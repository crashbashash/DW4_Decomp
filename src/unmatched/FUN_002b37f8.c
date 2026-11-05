/* 0x002b37f8 — FUN_002b37f8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004f57b8[4];
int *FUN_002b37f8(void) {
    return &DAT_004f57b8[0];
}
