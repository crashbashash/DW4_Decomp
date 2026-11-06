int FUN_002ea4b0();
int FUN_0030e9b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c1cf8[4];
extern int DAT_004c1d08[4];
extern int DAT_004c1d18[4];
extern int DAT_004c1d28[4];
extern void * DAT_00586cd8[4];
int thunk_igSemaphore_GetMetaObject();

void igPsx2Semaphore_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_00586cd8[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1cf8[0], 3);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 1);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c1d08[0], &DAT_004c1d18[0], &DAT_004c1d28[0], temp_s1);
    *(int *)((char *)(DAT_00586cd8[0]) + 64) = (int)(&thunk_igSemaphore_GetMetaObject);
}
