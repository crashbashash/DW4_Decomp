int FUN_002ba690();
int FUN_002c57c0();
int FUN_002dc7a0();
int FUN_002ea4b0();
int FUN_0030ec10(void*, unsigned long long);
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c16e0[4];
extern int DAT_004c1700[4];
extern int DAT_004c1720[4];
extern int DAT_004c1740[4];
extern int DAT_004c2600[4];
extern int DAT_004c2608[4];
extern void * DAT_00586a30[4];
int FUN_002cd5c0();
int thunk_igMemoryPool_GetMetaObject();

void igPageMemoryPool_InitFields(void) {
    void *temp_s1;
    int temp_s0;
    void *sp4C;
    void *temp_a0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;

    temp_s1 = (void *)(DAT_00586a30[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c16e0[0], 7);
    FUN_0030ec10(igMetaObject_GetFieldAt(temp_s1, temp_s0), 0xFFFFFFFFFFFFFFFFULL);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    *(int *)((char *)(temp_s2) + 56) = FUN_002c57c0();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    *(int *)((char *)(temp_s2_2) + 56) = FUN_002ba690();
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), -1);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    temp_a0 = (void *)(temp_s2_3);
    sp4C = (void *)DAT_004c2600[0];
    FUN_002dc7a0(temp_a0, &sp4C);
    *(int *)((char *)(temp_s2_3) + 52) = (int)(&FUN_002cd5c0);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6), DAT_004c2608[0]);
    igMetaObject_NameFields(temp_s1, &DAT_004c1700[0], &DAT_004c1720[0], &DAT_004c1740[0], temp_s0);
    *(int *)((char *)(DAT_00586a30[0]) + 64) = (int)(&thunk_igMemoryPool_GetMetaObject);
}
