/* 0x001a4f10 — igBitMask_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048cb98[4];
extern int DAT_0048cba0[4];
extern int DAT_0048cba8[4];
extern int DAT_0048cbb0[4];
extern int DAT_00561f58[4];
void igBitMask_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00561f58[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048cb98[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048cba0[0], &DAT_0048cba8[0], &DAT_0048cbb0[0], temp_s1);
}
