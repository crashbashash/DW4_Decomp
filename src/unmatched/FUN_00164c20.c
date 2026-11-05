/* 0x00164c20 — FUN_00164c20. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00554b34[4];
extern int DAT_00560710[4];
extern int DAT_00560714[4];
extern int DAT_00560718[4];
extern int DAT_00561098[4];
extern int DAT_005610b0[4];
extern int DAT_00586818[4];
int *FUN_00164c20(void) {
    if (DAT_00554b34[0] == 0) {
        DAT_00554b34[0] = 1;
        DAT_00560710[0] = DAT_00586818[0];
        DAT_00560714[0] = DAT_005610b0[0];
        DAT_00560718[0] = DAT_00561098[0];
    }
    return &DAT_00560710[0];
}
