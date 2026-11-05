/* 0x00135120 — igNormalizeNormalsStateAttr_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004861e0[4];
extern int DAT_004861e8[4];
extern int DAT_004861f0[4];
extern int DAT_004861f8[4];
extern int DAT_0055efc0[4];
void igNormalizeNormalsStateAttr_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0055efc0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004861e0[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004861e8[0], &DAT_004861f0[0], &DAT_004861f8[0], temp_s1);
}
