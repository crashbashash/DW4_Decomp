/* 0x00149aa0 — FUN_00149aa0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00487c50[4];
extern int DAT_00487c70[4];
extern int DAT_004d89d0[4];
extern int DAT_0055f8b8[4];
int FUN_00149aa0(void) {
    if (DAT_0055f8b8[0] == 0) {
        DAT_0055f8b8[0] = igMetaEnum_Create(&DAT_004d89d0[0], &DAT_00487c50[0], &DAT_00487c70[0], 6);
    }
    return DAT_0055f8b8[0];
}
