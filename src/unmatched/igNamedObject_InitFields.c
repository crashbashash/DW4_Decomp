/* 0x002be460 — igNamedObject_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStringMetaField_SetDefaultText();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bfbd8[4];
extern int DAT_004bfbe0[4];
extern int DAT_004bfbe8[4];
extern int DAT_004bfbf0[4];
extern int DAT_00585bd8[4];
void igNamedObject_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00585bd8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bfbd8[0], 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004bfbe0[0], &DAT_004bfbe8[0], &DAT_004bfbf0[0], temp_s1);
}
