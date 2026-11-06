int FUN_002ba690();
int FUN_002d3890();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c1c80[4];
extern int DAT_004c1ca0[4];
extern int DAT_004c1cc0[4];
extern int DAT_004c1ce0[4];
extern void * DAT_00586ca0[4];
int thunk_igThread_GetMetaObject();

void igPsx2Thread_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_00586ca0[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1c80[0], 6);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1) + 56) = FUN_002ba690();
    *(char *)((char *)(temp_s1) + 52) = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c1ca0[0], &DAT_004c1cc0[0], &DAT_004c1ce0[0], temp_s2);
    *(int *)((char *)(DAT_00586ca0[0]) + 64) = (int)(&thunk_igThread_GetMetaObject);
}
