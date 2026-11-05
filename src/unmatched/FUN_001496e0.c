/* 0x001496e0 — FUN_001496e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00487870[4];
extern int DAT_00487890[4];
extern int DAT_004d76a0[4];
extern int DAT_0055f868[4];
int FUN_001496e0(void) {
    if (DAT_0055f868[0] == 0) {
        DAT_0055f868[0] = igMetaEnum_Create(&DAT_004d76a0[0], &DAT_00487870[0], &DAT_00487890[0], 8);
    }
    return DAT_0055f868[0];
}
