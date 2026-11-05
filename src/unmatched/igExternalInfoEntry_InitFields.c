/* 0x002c5130 — igExternalInfoEntry_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ea4b0();
int igStringMetaField_SetDefaultText();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0c00[4];
extern int DAT_004c0c10[4];
extern int DAT_004c0c20[4];
extern int DAT_004c0c30[4];
extern int DAT_005863f8[4];
void igExternalInfoEntry_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_005863f8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0c00[0], 3);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1), 0);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), -1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004c0c10[0], &DAT_004c0c20[0], &DAT_004c0c30[0], temp_s1);
}
