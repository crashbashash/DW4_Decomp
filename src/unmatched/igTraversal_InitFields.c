int FUN_0019a720();
int FUN_002ebc00();
int FUN_002fe480();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048af10[4];
extern int DAT_0048af30[4];
extern int DAT_0048af50[4];
extern int DAT_0048af70[4];
extern int DAT_00561178[4];
int thunk_FUN_001e0470();

void igTraversal_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s0 = (void *)DAT_00561178[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048af10[0], 5);
    FUN_002ebc00(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1) + 56) = FUN_0019a720();
    igMetaObject_NameFields(temp_s0, &DAT_0048af30[0], &DAT_0048af50[0], &DAT_0048af70[0], temp_s2);
    FUN_002fe480(&thunk_FUN_001e0470);
}
