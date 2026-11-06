int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048b5d8[4];
extern int DAT_0048b5e8[4];
extern int DAT_0048b5f8[4];
extern int DAT_0048b608[4];
extern int DAT_005614d8[4];
void igSkeletonBoneInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005614d8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b5d8[0], 3);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), -1);
    igMetaObject_NameFields(temp_s0, &DAT_0048b5e8[0], &DAT_0048b5f8[0], &DAT_0048b608[0], temp_s1);
}
