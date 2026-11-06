int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00497c60[4];
extern int DAT_00497c68[4];
extern int DAT_00497c70[4];
extern int DAT_00497c78[4];
extern int DAT_0056d8c8[4];
void igLogInterface_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056d8c8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497c60[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00497c68[0], &DAT_00497c70[0], &DAT_00497c78[0], temp_s1);
}
