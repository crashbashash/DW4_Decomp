/* 0x0044c420 — igClearRenderer_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004cff68[4];
extern int DAT_004cff70[4];
extern int DAT_004cff78[4];
extern int DAT_004cff80[4];
extern int DAT_0058c1f0[4];
void igClearRenderer_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058c1f0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cff68[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cff70[0], &DAT_004cff78[0], &DAT_004cff80[0], temp_s1);
}
