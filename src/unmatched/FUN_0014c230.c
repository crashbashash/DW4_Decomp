/* 0x0014c230 — FUN_0014c230. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00488850[4];
extern int DAT_00488858[4];
extern int DAT_004dbf60[4];
extern int DAT_0055fb30[4];
int FUN_0014c230(void) {
    if (DAT_0055fb30[0] == 0) {
        DAT_0055fb30[0] = igMetaEnum_Create(&DAT_004dbf60[0], &DAT_00488850[0], &DAT_00488858[0], 2);
    }
    return DAT_0055fb30[0];
}
