/* 0x0012bf90 — FUN_0012bf90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0012b078();
extern int DAT_004854a0[4];
void FUN_0012bf90(int arg0, int arg1) {
    FUN_0012b078(DAT_004854a0[0], arg0, arg1);
}
