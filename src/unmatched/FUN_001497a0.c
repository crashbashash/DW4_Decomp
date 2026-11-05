/* 0x001497a0 — FUN_001497a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00487910[4];
extern int DAT_00487930[4];
extern int DAT_004d7a50[4];
extern int DAT_0055f878[4];
int FUN_001497a0(void) {
    if (DAT_0055f878[0] == 0) {
        DAT_0055f878[0] = igMetaEnum_Create(&DAT_004d7a50[0], &DAT_00487910[0], &DAT_00487930[0], 6);
    }
    return DAT_0055f878[0];
}
