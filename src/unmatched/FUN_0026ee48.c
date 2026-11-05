/* 0x0026ee48 — FUN_0026ee48. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();
extern int DAT_004a8eb8[4];
void FUN_0026ee48(void) {
    memset(&DAT_004a8eb8[0], 0, 0x3C0);
}
