/* 0x00149800 — FUN_00149800. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00487950[4];
extern int DAT_00487970[4];
extern int DAT_004d7b60[4];
extern int DAT_0055f880[4];
int FUN_00149800(void) {
    if (DAT_0055f880[0] == 0) {
        DAT_0055f880[0] = igMetaEnum_Create(&DAT_004d7b60[0], &DAT_00487950[0], &DAT_00487970[0], 5);
    }
    return DAT_0055f880[0];
}
