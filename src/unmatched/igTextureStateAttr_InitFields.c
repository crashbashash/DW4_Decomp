int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_00141710(void);  /* code at 0x141710, passed by address (was DAT_141710; docs/engine/function-inventory.md) */
extern int DAT_00485ad8[4];
extern int DAT_00485ae0[4];
extern int DAT_00485ae8[4];
extern int DAT_00485af0[4];
extern void * DAT_0055eca8[4];
void igTextureStateAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;
    temp_s0 = DAT_0055eca8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485ad8[0], 2);
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(int *)((char *)temp_s1 + 48) = (int)FUN_00141710;
    igMetaObject_NameFields(temp_s0, &DAT_00485ae0[0], &DAT_00485ae8[0], &DAT_00485af0[0], temp_s2);
}
