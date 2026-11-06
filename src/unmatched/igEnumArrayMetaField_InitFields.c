int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0f98[4];
extern int DAT_004c0fa0[4];
extern int DAT_004c0fa8[4];
extern int DAT_004c0fb0[4];
extern int DAT_005865b0[4];
void igEnumArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005865b0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0f98[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c0fa0[0], &DAT_004c0fa8[0], &DAT_004c0fb0[0], temp_s1);
}
