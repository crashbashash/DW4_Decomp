/* 0x00149500 — FUN_00149500. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_004877d0[4];
extern int DAT_004877f0[4];
extern int DAT_004d73d0[4];
extern int DAT_0055f840[4];
int FUN_00149500(void) {
    if (DAT_0055f840[0] == 0) {
        DAT_0055f840[0] = igMetaEnum_Create(&DAT_004d73d0[0], &DAT_004877d0[0], &DAT_004877f0[0], 8);
    }
    return DAT_0055f840[0];
}
