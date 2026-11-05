/* 0x00294a30 — FUN_00294a30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004bd258[4];
int *FUN_00294a30(void) {
    return &DAT_004bd258[0];
}
