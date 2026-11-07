extern "C" {
int FUN_00133e50(...);
int FUN_002d3890(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_CreateFields(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igObject_Destroy(...);
extern int DAT_0048c060[4];
extern int DAT_0048c068[4];
extern int DAT_0048c070[4];
extern int DAT_0048c078[4];
extern int DAT_004e2710[4];
extern void * DAT_00561a38[4];
extern int DAT_00561a40[4];
void FUN_0019fca0(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void FUN_0019fca0(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(DAT_00561a38[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048c060[0], 1);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e2710[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002d3890(temp_v0_2, 1);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_00561a40[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = FUN_00133e50();
    *(char *)((char *)(temp_s0) + 38) = 0;
    igMetaObject_NameFields(temp_s1, &DAT_0048c068[0], &DAT_0048c070[0], &DAT_0048c078[0], temp_s2);
}
