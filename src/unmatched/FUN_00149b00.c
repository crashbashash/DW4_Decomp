/* 0x00149b00 — FUN_00149b00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00487c88[4];
extern int DAT_00487c98[4];
extern int DAT_004d8a70[4];
extern int DAT_0055f8c0[4];
int FUN_00149b00(void) {
    if (DAT_0055f8c0[0] == 0) {
        DAT_0055f8c0[0] = igMetaEnum_Create(&DAT_004d8a70[0], &DAT_00487c88[0], &DAT_00487c98[0], 3);
    }
    return DAT_0055f8c0[0];
}
