int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048db20[4];
extern int DAT_0048db28[4];
extern int DAT_0048db30[4];
extern int DAT_0048db38[4];
extern int DAT_00562bc0[4];
void igMatrixObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562bc0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db20[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048db28[0], &DAT_0048db30[0], &DAT_0048db38[0], temp_s1);
}
