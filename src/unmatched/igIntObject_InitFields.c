/* 0x001e4f50 — igIntObject_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048db40[4];
extern int DAT_0048db48[4];
extern int DAT_0048db50[4];
extern int DAT_0048db58[4];
extern int DAT_00562bd0[4];
void igIntObject_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00562bd0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db40[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048db48[0], &DAT_0048db50[0], &DAT_0048db58[0], temp_s1);
}
