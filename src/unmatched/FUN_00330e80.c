/* 0x00330e80 — FUN_00330e80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00586d70[4];
int FUN_00330e80(void) {
    return DAT_00586d70[0];
}
