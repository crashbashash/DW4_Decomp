int FUN_002ba690();
int FUN_002c57c0();
int FUN_002dc7a0();
int FUN_002ea4b0();
int FUN_0030ec10(void *, unsigned __int128);
int FUN_0030eda0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c1a40[4];
extern int DAT_004c1a70[4];
extern int DAT_004c1aa0[4];
extern int DAT_004c1ad0[4];
extern int DAT_004c25f0[4];
extern int DAT_004c25f8[4];
extern void * DAT_00586b80[4];
int FUN_002ce1b0();
int thunk_igMemoryPool_GetMetaObject();

void igMallocMemoryPool_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_a0;
    void *sp4C;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)(DAT_00586b80[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c1a40[0], 0xA);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0), -1);
    FUN_0030ec10(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2), (unsigned long long)-1LL);
    FUN_0030eda0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), 4);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    *(int *)((char *)(temp_s2) + 56) = FUN_002c57c0();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    *(int *)((char *)(temp_s2_2) + 56) = FUN_002ba690();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    temp_a0 = (void *)(temp_s2_3);
    sp4C = (void *)DAT_004c25f0[0];
    FUN_002dc7a0(temp_a0, &sp4C);
    *(int *)((char *)(temp_s2_3) + 52) = (int)(&FUN_002ce1b0);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9), DAT_004c25f8[0]);
    igMetaObject_NameFields(temp_s1, &DAT_004c1a70[0], &DAT_004c1aa0[0], &DAT_004c1ad0[0], temp_s0);
    *(int *)((char *)(DAT_00586b80[0]) + 64) = (int)(&thunk_igMemoryPool_GetMetaObject);
}
