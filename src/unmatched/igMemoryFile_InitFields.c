/* 0x2c0940 — igMemoryFile_InitFields. Verified byte-identical by tools/verify.py (wave3 sweep). */
int FUN_002fe480();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0290[4];
extern int DAT_004c02a0[4];
extern int DAT_004c02b0[4];
extern int DAT_004c02c0[4];
extern void * DAT_00585f18[4];
int thunk_FUN_002ef9d0();
int thunk_igFile_GetMetaObject();

void igMemoryFile_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)(DAT_00585f18[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0290[0], 4);
    igMetaObject_NameFields(temp_s0, &DAT_004c02a0[0], &DAT_004c02b0[0], &DAT_004c02c0[0], temp_s1);
    *(int *)((char *)(DAT_00585f18[0]) + 64) = (int)(&thunk_igFile_GetMetaObject);
    FUN_002fe480(&thunk_FUN_002ef9d0);
}
