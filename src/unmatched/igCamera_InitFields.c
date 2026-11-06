int FUN_002dc7a0();
int FUN_002e3810(void *, float);
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048ca10[4];
extern int DAT_0048ca30[4];
extern int DAT_0048ca50[4];
extern int DAT_0048ca70[4];
extern int DAT_0048ca90[4];
extern int DAT_00561ea0[4];
int FUN_001a47d0();

void igCamera_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)DAT_00561ea0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048ca10[0], 7);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_0048ca90[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_001a47d0);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 45.0f);
    igMetaObject_NameFields(temp_s0, &DAT_0048ca30[0], &DAT_0048ca50[0], &DAT_0048ca70[0], temp_s2);
}
