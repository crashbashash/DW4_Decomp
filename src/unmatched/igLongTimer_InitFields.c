int FUN_002d3890();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c04a0[4];
extern int DAT_004c04b0[4];
extern int DAT_004c04c0[4];
extern int DAT_004c04d0[4];
extern void * DAT_00586028[4];
extern void thunk_igPsx2LongTimer_GetMetaObject(void);
void igLongTimer_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    temp_s0 = (void *)(DAT_00586028[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c04a0[0], 4);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c04b0[0], &DAT_004c04c0[0], &DAT_004c04d0[0], temp_s1);
    *(int *)((char *)(DAT_00586028[0]) + 60) = (int)thunk_igPsx2LongTimer_GetMetaObject;
}
