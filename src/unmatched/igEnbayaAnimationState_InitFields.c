int FUN_002d3890();
int FUN_002fe480();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_001a21a0(void);
extern int DAT_0048c340[4];
extern int DAT_0048c348[4];
extern int DAT_0048c350[4];
extern int DAT_0048c358[4];
extern int DAT_00561b80[4];
void igEnbayaAnimationState_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00561b80[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048c340[0], 2);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s1)) + 38) = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048c348[0], &DAT_0048c350[0], &DAT_0048c358[0], temp_s1);
    FUN_002fe480(FUN_001a21a0);
}
