int FUN_002d3890();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486728[4];
extern int DAT_00486730[4];
extern int DAT_00486738[4];
extern int DAT_00486740[4];
extern int DAT_0055f218[4];
void igDepthWriteStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f218[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486728[0], 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486730[0], &DAT_00486738[0], &DAT_00486740[0], temp_s1);
}
