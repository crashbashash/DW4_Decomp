int FUN_002d3890();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486248[4];
extern int DAT_00486250[4];
extern int DAT_00486258[4];
extern int DAT_00486260[4];
extern int DAT_0055f000[4];
void igMatrixOptStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f000[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486248[0], 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486250[0], &DAT_00486258[0], &DAT_00486260[0], temp_s1);
}
