/* 0x0014c290 — FUN_0014c290. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00488860[4];
extern int DAT_00488868[4];
extern int DAT_004dbfe0[4];
extern int DAT_0055fb38[4];
int FUN_0014c290(void) {
    if (DAT_0055fb38[0] == 0) {
        DAT_0055fb38[0] = igMetaEnum_Create(&DAT_004dbfe0[0], &DAT_00488860[0], &DAT_00488868[0], 2);
    }
    return DAT_0055fb38[0];
}
