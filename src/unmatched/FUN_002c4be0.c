/* 0x002c4be0 — FUN_002c4be0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c0ae8[4];
extern int DAT_004c0af8[4];
extern int DAT_004f7668[4];
extern int DAT_005863a0[4];
int FUN_002c4be0(void) {
    if (DAT_005863a0[0] == 0) {
        DAT_005863a0[0] = igMetaEnum_Create(&DAT_004f7668[0], &DAT_004c0ae8[0], &DAT_004c0af8[0], 3);
    }
    return DAT_005863a0[0];
}
