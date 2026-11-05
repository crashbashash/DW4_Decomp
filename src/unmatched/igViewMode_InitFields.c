/* 0x0045d090 — igViewMode_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d1680[4];
extern int DAT_004d1688[4];
extern int DAT_004d1690[4];
extern int DAT_004d1698[4];
extern int DAT_0058ccf8[4];
void igViewMode_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058ccf8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1680[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004d1688[0], &DAT_004d1690[0], &DAT_004d1698[0], temp_s1);
}
