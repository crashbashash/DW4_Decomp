int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048db60[4];
extern int DAT_0048db68[4];
extern int DAT_0048db70[4];
extern int DAT_0048db78[4];
extern int DAT_00562be0[4];
void igFloatObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562be0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048db60[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048db68[0], &DAT_0048db70[0], &DAT_0048db78[0], temp_s1);
}
