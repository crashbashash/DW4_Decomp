/* 0x00149980 — FUN_00149980. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00487a10[4];
extern int DAT_00487a30[4];
extern int DAT_004d7ed0[4];
extern int DAT_0055f8a0[4];
int FUN_00149980(void) {
    if (DAT_0055f8a0[0] == 0) {
        DAT_0055f8a0[0] = igMetaEnum_Create(&DAT_004d7ed0[0], &DAT_00487a10[0], &DAT_00487a30[0], 6);
    }
    return DAT_0055f8a0[0];
}
