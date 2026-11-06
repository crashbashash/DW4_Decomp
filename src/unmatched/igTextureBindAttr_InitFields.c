int FUN_00132ba0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_00140e40(void);
extern int DAT_00485cb0[4];
extern int DAT_00485cb8[4];
extern int DAT_00485cc0[4];
extern int DAT_00485cc8[4];
extern void * DAT_0055ed88[4];
void igTextureBindAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;
    temp_s0 = DAT_0055ed88[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485cb0[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00132ba0();
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(int *)((char *)temp_s1 + 48) = (int)FUN_00140e40;
    igMetaObject_NameFields(temp_s0, &DAT_00485cb8[0], &DAT_00485cc0[0], &DAT_00485cc8[0], temp_s2);
}
