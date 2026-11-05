int FUN_0018e470();
int FUN_0019cbe0();
int FUN_002e3810(void *, float);
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048c010[4];
extern int DAT_0048c020[4];
extern int DAT_0048c030[4];
extern int DAT_0048c040[4];
extern int DAT_00561a10[4];
void igGraphPath_InitFields(void) {
    void *temp_s0;
    void *temp_a0;
    void *temp_s1;
    struct { int a; int b; int c; } z;
    int temp_s2;

    temp_s0 = (void *)DAT_00561a10[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048c010[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_0019cbe0();
    *(char *)((char *)(temp_s1) + 36) = 3;
    *(char *)((char *)(temp_s1) + 52) = 1;
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    z.a = 0;
    z.b = 0;
    z.c = 0;
    FUN_0018e470(temp_a0, &z);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1.0f);
    igMetaObject_NameFields(temp_s0, &DAT_0048c020[0], &DAT_0048c030[0], &DAT_0048c040[0], temp_s2);
}
