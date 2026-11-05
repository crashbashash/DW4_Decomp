/* 0x001493e0 — FUN_001493e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00487768[4];
extern int DAT_00487770[4];
extern int DAT_004d70e0[4];
extern int DAT_0055f828[4];
int FUN_001493e0(void) {
    if (DAT_0055f828[0] == 0) {
        DAT_0055f828[0] = igMetaEnum_Create(&DAT_004d70e0[0], &DAT_00487768[0], &DAT_00487770[0], 2);
    }
    return DAT_0055f828[0];
}
