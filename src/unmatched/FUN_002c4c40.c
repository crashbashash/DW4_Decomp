/* 0x002c4c40 — FUN_002c4c40. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c0b10[4];
extern int DAT_004c0b40[4];
extern int DAT_004f7708[4];
extern int DAT_005863a8[4];
int FUN_002c4c40(void) {
    if (DAT_005863a8[0] == 0) {
        DAT_005863a8[0] = igMetaEnum_Create(&DAT_004f7708[0], &DAT_004c0b10[0], &DAT_004c0b40[0], 9);
    }
    return DAT_005863a8[0];
}
