int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0098[4];
extern int DAT_004d00a0[4];
extern int DAT_004d00a8[4];
extern int DAT_004d00b0[4];
extern int DAT_0058c278[4];
void igRadioGroupModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c278[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0098[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004d00a0[0], &DAT_004d00a8[0], &DAT_004d00b0[0], temp_s1);
}
