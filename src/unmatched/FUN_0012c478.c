/* 0x0012c478 — FUN_0012c478. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0012c248();
extern int DAT_004854a0[4];
void FUN_0012c478(int arg0, int arg1, int arg2) {
    FUN_0012c248(DAT_004854a0[0], arg0, arg1, arg2);
}
