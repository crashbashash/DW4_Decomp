/* 0x0014d510 — FUN_0014d510. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00488cf0[4];
extern int DAT_00488d00[4];
extern int DAT_004dc7c0[4];
extern int DAT_0055fd08[4];
int FUN_0014d510(void) {
    if (DAT_0055fd08[0] == 0) {
        DAT_0055fd08[0] = igMetaEnum_Create(&DAT_004dc7c0[0], &DAT_00488cf0[0], &DAT_00488d00[0], 3);
    }
    return DAT_0055fd08[0];
}
