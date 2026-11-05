/* 0x001ea3f0 — FUN_001ea3f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00204240();
extern int DAT_00562d80[4];
extern int DAT_00562d88[4];
void FUN_001ea3f0(void) {
    DAT_00562d88[0] = 0;
    DAT_00562d80[0] = 0x400000;
    FUN_00204240(3, &DAT_00562d88[0]);
}
