/* 0x00149920 — FUN_00149920. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_004879f0[4];
extern int DAT_00487a00[4];
extern int DAT_004d7db0[4];
extern int DAT_0055f898[4];
int FUN_00149920(void) {
    if (DAT_0055f898[0] == 0) {
        DAT_0055f898[0] = igMetaEnum_Create(&DAT_004d7db0[0], &DAT_004879f0[0], &DAT_00487a00[0], 4);
    }
    return DAT_0055f898[0];
}
