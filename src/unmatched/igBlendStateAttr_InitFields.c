/* 0x001397b0 — igBlendStateAttr_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004869e0[4];
extern int DAT_004869e8[4];
extern int DAT_004869f0[4];
extern int DAT_004869f8[4];
extern int DAT_0055f348[4];
void igBlendStateAttr_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0055f348[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004869e0[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004869e8[0], &DAT_004869f0[0], &DAT_004869f8[0], temp_s1);
}
