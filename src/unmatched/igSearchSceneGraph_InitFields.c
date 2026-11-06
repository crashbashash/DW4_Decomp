int FUN_002274a0();
int FUN_002be610();
int FUN_002dc7a0();
int igStringMetaField_SetDefaultText();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004982a0[4];
extern int DAT_004982b0[4];
extern int DAT_004982c0[4];
extern int DAT_004982d0[4];
extern int DAT_004982e0[4];
extern int DAT_004e9da0[4];
extern int DAT_0056dc60[4];
int FUN_00238d70();

void igSearchSceneGraph_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dc60[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004982a0[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_002274a0();
    *(unsigned char *)((char *)(temp_s1) + 52) = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), &DAT_004e9da0[0]);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_002be610();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    FUN_002dc7a0(temp_v0, &DAT_004982e0[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_00238d70);
    igMetaObject_NameFields(temp_s0, &DAT_004982b0[0], &DAT_004982c0[0], &DAT_004982d0[0], temp_s2);
}
