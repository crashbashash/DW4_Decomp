int FUN_0018e470();
int FUN_002d3890();
int FUN_0044ff40();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d04b0[4];
extern int DAT_004d04d0[4];
extern int DAT_004d04f0[4];
extern int DAT_004d0510[4];
extern int DAT_0058c438[4];
void igGuiComponentModel_InitFields(void) {
    void *temp_s0;
    void *temp_a0;
    void *temp_s1;
    struct { int a; int b; int c; } z;
    int temp_s2;

    temp_s0 = (void *)DAT_0058c438[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d04b0[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_0044ff40();
    *(char *)((char *)(temp_s1) + 60) = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    z.a = 0;
    z.b = 0;
    z.c = 0;
    FUN_0018e470(temp_a0, &z);
    igMetaObject_NameFields(temp_s0, &DAT_004d04d0[0], &DAT_004d04f0[0], &DAT_004d0510[0], temp_s2);
}
