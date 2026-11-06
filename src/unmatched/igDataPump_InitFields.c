int FUN_001e5530();
int FUN_002beca0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
int igStringMetaField_SetDefaultText();
extern int DAT_0048dbf0[4];
extern int DAT_0048dc10[4];
extern int DAT_0048dc30[4];
extern int DAT_0048dc50[4];
extern int DAT_00562c20[4];
extern int DAT_00587198[4];
void igDataPump_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00562c20[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048dbf0[0], 5);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_v0) + 56) = (int)((int) DAT_00587198[0]);
    *(char *)((char *)(temp_v0) + 52) = 1;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1) + 56) = FUN_002beca0();
    *(char *)((char *)(temp_s1) + 38) = 0;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 0);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_001e5530();
    igMetaObject_NameFields(temp_s0, &DAT_0048dc10[0], &DAT_0048dc30[0], &DAT_0048dc50[0], temp_s2);
}
