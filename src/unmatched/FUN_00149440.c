/* 0x00149440 — FUN_00149440. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00487778[4];
extern int DAT_00487780[4];
extern int DAT_004d7150[4];
extern int DAT_0055f830[4];
int FUN_00149440(void) {
    if (DAT_0055f830[0] == 0) {
        DAT_0055f830[0] = igMetaEnum_Create(&DAT_004d7150[0], &DAT_00487778[0], &DAT_00487780[0], 2);
    }
    return DAT_0055f830[0];
}
