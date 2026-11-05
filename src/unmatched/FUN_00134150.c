/* 0x00134150 — FUN_00134150. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00485f98[4];
extern int DAT_00485fa8[4];
extern int DAT_004d5140[4];
extern int DAT_0055eed0[4];
int FUN_00134150(void) {
    if (DAT_0055eed0[0] == 0) {
        DAT_0055eed0[0] = igMetaEnum_Create(&DAT_004d5140[0], &DAT_00485f98[0], &DAT_00485fa8[0], 3);
    }
    return DAT_0055eed0[0];
}
