int FUN_002d3890();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0190[4];
extern int DAT_004c01d0[4];
extern int DAT_004c0210[4];
extern int DAT_004c0250[4];
extern void * DAT_00585ea0[4];
extern void thunk_igArenaMemoryPool_GetMetaObject(void);

void igMemoryPool_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)(DAT_00585ea0[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0190[0], 0xE);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c01d0[0], &DAT_004c0210[0], &DAT_004c0250[0], temp_s1);
    *(int *)((char *)(DAT_00585ea0[0]) + 60) = (int)thunk_igArenaMemoryPool_GetMetaObject;
}
