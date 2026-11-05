int FUN_002dc7a0();
int FUN_0030e9b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00485e70[4];
extern int DAT_00485e90[4];
extern int DAT_00485eb0[4];
extern int DAT_00485ed0[4];
extern int DAT_00485ef0[4];
extern int DAT_00485ef8[4];
extern int DAT_00485f00[4];
extern int DAT_00485f08[4];
extern int DAT_0055ee50[4];
void FUN_001494a0(void);
void DAT_001494a0(void);
void g_001494a0(void);
void FUN_00149500(void);

void igStencilFunctionAttr_InitFields(void) {
    int temp_s0;
    void *temp_s1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;

    temp_s1 = (void *)DAT_0055ee50[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_00485e70[0], 7);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    FUN_002dc7a0(temp_v0, &DAT_00485ef0[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)FUN_00149500;
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2), -1);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), -1);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    FUN_002dc7a0(temp_v0_2, &DAT_00485ef8[0]);
    *(int *)((char *)(temp_v0_2) + 52) = (int)FUN_001494a0;
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    FUN_002dc7a0(temp_v0_3, &DAT_00485f00[0]);
    *(int *)((char *)(temp_v0_3) + 52) = (int)DAT_001494a0;
    temp_v0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    FUN_002dc7a0(temp_v0_4, &DAT_00485f08[0]);
    *(int *)((char *)(temp_v0_4) + 52) = (int)g_001494a0;
    igMetaObject_NameFields(temp_s1, &DAT_00485e90[0], &DAT_00485eb0[0], &DAT_00485ed0[0], temp_s0);
}
