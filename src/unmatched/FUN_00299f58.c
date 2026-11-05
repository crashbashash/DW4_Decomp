/* 0x00299f58 — FUN_00299f58. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004be8a0[4];
int *FUN_00299f58(void) {
    return &DAT_004be8a0[0];
}
