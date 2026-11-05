/* 0x00269c60 — FUN_00269c60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();
extern int DAT_004a7f10[4];
int FUN_00269c60(void) {
    memset(&DAT_004a7f10[0], 0, 0xF00);
    return 1;
}
