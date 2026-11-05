/* 0x001f8750 — FUN_001f8750. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00491278[4];
extern int DAT_00491478[4];
extern long long DAT_0056af18[4];
void FUN_001f8750(int arg0) {
    DAT_00491278[0] = arg0;
    DAT_00491478[0] |= 0x84;
    DAT_0056af18[0] += 1;
}
