int FUN_002d3890();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486748[4];
extern int DAT_00486750[4];
extern int DAT_00486758[4];
extern int DAT_00486760[4];
extern int DAT_0055f228[4];
void igDepthStateAttr_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0055f228[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486748[0], 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486750[0], &DAT_00486758[0], &DAT_00486760[0], temp_s1);
}
