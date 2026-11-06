int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048dc68[4];
extern int DAT_0048dc70[4];
extern int DAT_0048dc78[4];
extern int DAT_0048dc80[4];
extern int DAT_00562c50[4];
void igBoolObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562c50[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048dc68[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048dc70[0], &DAT_0048dc78[0], &DAT_0048dc80[0], temp_s1);
}
