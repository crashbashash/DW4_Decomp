int FUN_00194dd0();
int FUN_001a6bf0();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048d2c0[4];
extern int DAT_0048d2e0[4];
extern int DAT_0048d300[4];
extern int DAT_0048d320[4];
extern int DAT_00562268[4];
void igAnimationCombinerBoneInfo_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_00562268[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d2c0[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_001a6bf0();
    *(char *)((char *)(temp_s1) + 36) = 2;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_00194dd0();
    *(char *)((char *)(temp_s1_2) + 36) = 2;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    FUN_002ea4b0(temp_v0, 1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7), -1);
    igMetaObject_NameFields(temp_s0, &DAT_0048d2e0[0], &DAT_0048d300[0], &DAT_0048d320[0], temp_s2);
}
