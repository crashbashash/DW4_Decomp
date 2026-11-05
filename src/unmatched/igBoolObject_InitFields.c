/* 0x001e5d70 — igBoolObject_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048dc68[4];
extern int DAT_0048dc70[4];
extern int DAT_0048dc78[4];
extern int DAT_0048dc80[4];
extern int DAT_00562c50[4];
void igBoolObject_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00562c50[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048dc68[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048dc70[0], &DAT_0048dc78[0], &DAT_0048dc80[0], temp_s1);
}
