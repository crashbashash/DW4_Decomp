/* 0x001e7340 — FUN_001e7340. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00562b88[4];
int FUN_001e7340(void) {
    return DAT_00562b88[0];
}
