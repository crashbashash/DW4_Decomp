int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048b140[4];
extern int DAT_0048b148[4];
extern int DAT_0048b150[4];
extern int DAT_0048b158[4];
extern int DAT_00561280[4];
void igTransformRecorder_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00561280[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b140[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_0048b148[0], &DAT_0048b150[0], &DAT_0048b158[0], temp_s1);
}
