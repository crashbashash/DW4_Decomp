/* 0x00164aa0 — FUN_00164aa0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00554b28[4];
extern int DAT_005606a0[4];
extern int DAT_005606a4[4];
extern int DAT_005606a8[4];
extern int DAT_005606ac[4];
extern int DAT_005606b0[4];
extern int DAT_005610b8[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
extern int DAT_00586898[4];
int *FUN_00164aa0(void) {
    if (DAT_00554b28[0] == 0) {
        DAT_00554b28[0] = 1;
        DAT_005606a0[0] = DAT_005610b8[0];
        DAT_005606a4[0] = DAT_00586898[0];
        DAT_005606a8[0] = DAT_00586818[0];
        DAT_005606ac[0] = DAT_00586830[0];
        DAT_005606b0[0] = DAT_00586840[0];
    }
    return &DAT_005606a0[0];
}
