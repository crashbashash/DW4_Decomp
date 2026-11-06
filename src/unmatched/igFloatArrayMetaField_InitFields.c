int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0ac8[4];
extern int DAT_004c0ad0[4];
extern int DAT_004c0ad8[4];
extern int DAT_004c0ae0[4];
extern int DAT_00586388[4];
void igFloatArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00586388[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0ac8[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c0ad0[0], &DAT_004c0ad8[0], &DAT_004c0ae0[0], temp_s1);
}
