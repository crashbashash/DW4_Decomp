/* 0x00129ba0 — FUN_00129ba0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00129a30();
extern int DAT_004854a0[4];
void FUN_00129ba0(int arg0) {
    FUN_00129a30(DAT_004854a0[0], arg0);
}
