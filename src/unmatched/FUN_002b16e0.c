/* 0x002b16e0 — FUN_002b16e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004f5330[4];
int *FUN_002b16e0(void) {
    return &DAT_004f5330[0];
}
