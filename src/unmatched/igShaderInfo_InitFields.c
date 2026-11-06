int FUN_00198fa0();
int FUN_002fe480();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048b620[4];
extern int DAT_0048b628[4];
extern int DAT_0048b630[4];
extern int DAT_0048b638[4];
extern int DAT_00561500[4];
extern void thunk_FUN_001d8b90(void);

void igShaderInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00561500[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b620[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00198fa0();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields(temp_s0, &DAT_0048b628[0], &DAT_0048b630[0], &DAT_0048b638[0], temp_s2);
    FUN_002fe480((int)thunk_FUN_001d8b90);
}
