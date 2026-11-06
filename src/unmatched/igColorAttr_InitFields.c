int FUN_0018e670();
int FUN_0030e9b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486918[4];
extern int DAT_00486920[4];
extern int DAT_00486928[4];
extern int DAT_00486930[4];
extern int DAT_0055f2e0[4];
int FUN_0013c870();

void igColorAttr_InitFields(void) {
    void *temp_s0;
    void *temp_a0;
    void *temp_s1;
    void *temp_v0;
    int sp40[4];
    int temp_s2;

    temp_s0 = (void *)DAT_0055f2e0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486918[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    temp_a0 = (void *)(temp_s1);
    sp40[0] = 0x3F800000;
    sp40[1] = 0x3F800000;
    sp40[2] = 0x3F800000;
    sp40[3] = 0x3F800000;
    FUN_0018e670(temp_a0, sp40);
    *(int *)((char *)(temp_s1) + 48) = (int)(&FUN_0013c870);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_0030e9b0(temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00486920[0], &DAT_00486928[0], &DAT_00486930[0], temp_s2);
}
