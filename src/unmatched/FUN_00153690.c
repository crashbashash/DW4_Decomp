/* 0x00153690 — FUN_00153690. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaEnum_Create();
extern int DAT_00489f70[4];
extern int DAT_00489fa0[4];
extern int DAT_004de540[4];
extern int DAT_00560580[4];
int FUN_00153690(void) {
    if (DAT_00560580[0] == 0) {
        DAT_00560580[0] = igMetaEnum_Create(&DAT_004de540[0], &DAT_00489f70[0], &DAT_00489fa0[0], 0xC);
    }
    return DAT_00560580[0];
}
