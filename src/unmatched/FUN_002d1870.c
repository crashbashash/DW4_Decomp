/* 0x002d1870 — FUN_002d1870. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create(int *, int, int, int);
extern int DAT_004f7910[4];
extern int DAT_00586dc0[4];
int FUN_002d1870(void) {
    if (DAT_00586dc0[0] == 0) {
        DAT_00586dc0[0] = igMetaEnum_Create(&DAT_004f7910[0], 0, 0, 0);
    }
    return DAT_00586dc0[0];
}
