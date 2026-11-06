int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c10c8[4];
extern int DAT_004c10d0[4];
extern int DAT_004c10d8[4];
extern int DAT_004c10e0[4];
extern int DAT_00586648[4];
void igDoubleArrayMetaField_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00586648[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c10c8[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c10d0[0], &DAT_004c10d8[0], &DAT_004c10e0[0], temp_s1);
}
