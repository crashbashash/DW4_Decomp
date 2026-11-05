/* 0x00238d70 — FUN_00238d70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00498270[4];
extern int DAT_00498280[4];
extern int DAT_004e9d20[4];
extern int DAT_0056dc58[4];
int FUN_00238d70(void) {
    if (DAT_0056dc58[0] == 0) {
        DAT_0056dc58[0] = igMetaEnum_Create(&DAT_004e9d20[0], &DAT_00498270[0], &DAT_00498280[0], 3);
    }
    return DAT_0056dc58[0];
}
