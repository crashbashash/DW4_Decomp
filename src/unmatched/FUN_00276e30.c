/* 0x00276e30 — FUN_00276e30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004aba04[4];
void FUN_00276e30(int arg0) {
    DAT_004aba04[0] = arg0;
}
