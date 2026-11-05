/* 0x001340f0 — FUN_001340f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00485f88[4];
extern int DAT_00485f90[4];
extern int DAT_004d5080[4];
extern int DAT_0055eec8[4];
int FUN_001340f0(void) {
    if (DAT_0055eec8[0] == 0) {
        DAT_0055eec8[0] = igMetaEnum_Create(&DAT_004d5080[0], &DAT_00485f88[0], &DAT_00485f90[0], 2);
    }
    return DAT_0055eec8[0];
}
