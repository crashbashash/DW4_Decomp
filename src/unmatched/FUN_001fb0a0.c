/* 0x001fb0a0 — FUN_001fb0a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00491270[4];
extern int DAT_00491478[4];
extern int DAT_0056aed0[4];
extern long long DAT_0056af18[4];
void FUN_001fb0a0(int arg0) {
    DAT_0056aed0[0] = arg0;
    DAT_00491270[0] = 1;
    DAT_0056af18[0] += 1;
    DAT_00491478[0] |= 5;
}
