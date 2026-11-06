int FUN_0014a040();
int FUN_002d3890();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
int igStringMetaField_SetDefaultText();
extern int DAT_00487450[4];
extern int DAT_00487480[4];
extern int DAT_004874b0[4];
extern int DAT_004874e0[4];
extern void * DAT_0055f6c8[4];
extern void thunk_igWindow_GetMetaObject(void);

void igPsx2Window_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055f6c8[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487450[0], 0xC);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2), 0x280);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 0x1C0);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1) + 56) = FUN_0014a040();
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 0);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9), 0x18);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA), 8);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB), 0x20);
    igMetaObject_NameFields(temp_s0, &DAT_00487480[0], &DAT_004874b0[0], &DAT_004874e0[0], temp_s2);
    *(int *)((char *)(DAT_0055f6c8[0]) + 64) = (int)thunk_igWindow_GetMetaObject;
}
