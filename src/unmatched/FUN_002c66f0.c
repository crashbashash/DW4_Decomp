/* 0x002c66f0 — FUN_002c66f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c0fb8[4];
extern int DAT_004c0fc0[4];
extern int DAT_004f7f00[4];
extern int DAT_005865c8[4];
int FUN_002c66f0(void) {
    if (DAT_005865c8[0] == 0) {
        DAT_005865c8[0] = igMetaEnum_Create(&DAT_004f7f00[0], &DAT_004c0fb8[0], &DAT_004c0fc0[0], 2);
    }
    return DAT_005865c8[0];
}
