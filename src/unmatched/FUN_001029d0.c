/* 0x001029d0 — FUN_001029d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00100c50();
extern int DAT_00522440[4];
extern int DAT_00522480[4];
extern int DAT_00546fb0[4];
extern int DAT_00554858[4];
void FUN_001029d0(void) {
    FUN_00100c50(&DAT_00522440[0], &DAT_00522480[0], &DAT_00546fb0[0], &DAT_00554858[0]);
}
