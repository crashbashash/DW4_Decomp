/* 0x001495c0 — FUN_001495c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00487830[4];
extern int DAT_00487840[4];
extern int DAT_004d74c0[4];
extern int DAT_0055f850[4];
int FUN_001495c0(void) {
    if (DAT_0055f850[0] == 0) {
        DAT_0055f850[0] = igMetaEnum_Create(&DAT_004d74c0[0], &DAT_00487830[0], &DAT_00487840[0], 3);
    }
    return DAT_0055f850[0];
}
