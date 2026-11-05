/* 0x00274d08 — FUN_00274d08. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();
extern int DAT_004ab430[4];
void FUN_00274d08(void) {
    memset(&DAT_004ab430[0], 0, 0x10);
}
