int FUN_00459380();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0ac0[4];
extern int DAT_004d0ac8[4];
extern int DAT_004d0ad0[4];
extern int DAT_004d0ad8[4];
extern int DAT_0058c770[4];
void igViewerAction_InitFields(void) {
    void *f2;
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c770[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0ac0[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00459380();
    *(char *)((char *)(temp_s1) + 60) = 0;
    f2 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(short *)((char *)f2 + 20) = 0xC;
    igMetaObject_NameFields(temp_s0, &DAT_004d0ac8[0], &DAT_004d0ad0[0], &DAT_004d0ad8[0], temp_s2);
}
