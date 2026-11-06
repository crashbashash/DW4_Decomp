int FUN_002dc7a0();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
int igStringMetaField_SetDefaultText();
extern int DAT_004c0b70[4];
extern int DAT_004c0b90[4];
extern int DAT_004c0bb0[4];
extern int DAT_004c0bd0[4];
extern int DAT_004c0bf0[4];
extern int DAT_004c0bf8[4];
extern int DAT_004f77d0[4];
extern void * DAT_005863b0[4];
int FUN_002c4be0();
int FUN_002c4c40();
int thunk_igPsx2File_GetMetaObject();

void igFile_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)(DAT_005863b0[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0b70[0], 8);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2), &DAT_004f77d0[0]);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002dc7a0(temp_v0, &DAT_004c0bf0[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_002c4be0);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    FUN_002dc7a0(temp_v0_2, &DAT_004c0bf8[0]);
    *(int *)((char *)(temp_v0_2) + 52) = (int)(&FUN_002c4c40);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)) + 38) = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0x100000);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 0x100000);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 0x1000);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c0b90[0], &DAT_004c0bb0[0], &DAT_004c0bd0[0], temp_s2);
    *(int *)((char *)(DAT_005863b0[0]) + 60) = (int)(&thunk_igPsx2File_GetMetaObject);
}
