/* 0x00147030 — FUN_00147030. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00487580[4];
extern int DAT_004875a0[4];
extern int DAT_004d6e30[4];
extern int DAT_0055f758[4];
int FUN_00147030(void) {
    if (DAT_0055f758[0] == 0) {
        DAT_0055f758[0] = igMetaEnum_Create(&DAT_004d6e30[0], &DAT_00487580[0], &DAT_004875a0[0], 8);
    }
    return DAT_0055f758[0];
}
