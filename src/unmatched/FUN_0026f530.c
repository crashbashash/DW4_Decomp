/* 0x0026f530 — FUN_0026f530. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026f500();
extern int DAT_004a9280[4];
void FUN_0026f530(int arg0) {
    FUN_0026f500(&DAT_004a9280[0], arg0, 0);
}
