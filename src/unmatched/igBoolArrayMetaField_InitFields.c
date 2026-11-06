int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c1580[4];
extern int DAT_004c1588[4];
extern int DAT_004c1590[4];
extern int DAT_004c1598[4];
extern int DAT_00586998[4];
void igBoolArrayMetaField_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00586998[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1580[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c1588[0], &DAT_004c1590[0], &DAT_004c1598[0], temp_s1);
}
