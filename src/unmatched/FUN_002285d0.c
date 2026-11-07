int FUN_002b9120();
int FUN_002b9200();
int FUN_002be610();
int FUN_002c8e50();
int FUN_002c8f30();
int FUN_002eb010();
int Memory_GetAllocatorBySelector();
int ObjectList_AppendRetained();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
void *StringPool_Intern();
int igMetaField_FinalizeDescriptor();
int igMetaField_SetFieldName();
int igMetaObject_EnsureRegistered();
void *igObjectRefMetaField_Create();
int igObject_Destroy();
extern int DAT_004e7ce8[4];
extern int DAT_004e7d70[4];
extern int DAT_004e7d80[4];
extern int DAT_00586f20[4];
extern int DAT_00587040[4];
void FUN_002285d0(int arg0) {
    void *sp3C;
    void *sp38;
    void *sp34;
    int *temp_a1;
    int *temp_a1_2;
    int *temp_a1_3;
    int temp_v0;
    int temp_v0_2;
    int temp_v0_3;
    int var_v0_2;
    int var_v0_4;
    int var_v0_6;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *var_v0;
    void *var_v0_3;
    void *var_v0_5;

    temp_s0 = (void *)(igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_004e7d70[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004e7d70[0]));
    }
    sp3C = (void *)(var_v0);
    igMetaField_SetFieldName(temp_s0, &sp3C);
    if (sp3C != 0) {
        temp_a1 = (int *)((char *)sp3C - 8);
        temp_v0 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *(int *)((char *)(temp_s0) + 8) = 0;
    *(int *)((char *)(temp_s0) + 56) = FUN_002be610();
    igMetaField_FinalizeDescriptor(temp_s0);
    ObjectList_AppendRetained(arg0, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
    temp_s0_2 = (void *)(igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_004e7ce8[0] == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_4 = FUN_002eb010(0x10);
            if (var_v0_4 != 0) {
                var_v0_4 = StringPool_Construct(var_v0_4);
            }
            DAT_00586f20[0] = var_v0_4;
        }
        var_v0_3 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004e7ce8[0]));
    }
    sp38 = (void *)(var_v0_3);
    igMetaField_SetFieldName(temp_s0_2, &sp38);
    if (sp38 != 0) {
        temp_a1_2 = (int *)((char *)sp38 - 8);
        temp_v0_2 = *(int *)((char *)(sp38) - 4) - 1;
        *(int *)((char *)(sp38) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    *(int *)((char *)(temp_s0_2) + 8) = 4;
    *(int *)((char *)(temp_s0_2) + 56) = FUN_002c8e50();
    *(char *)((char *)(temp_s0_2) + 52) = 1;
    igMetaField_FinalizeDescriptor(temp_s0_2);
    ObjectList_AppendRetained(arg0, temp_s0_2);
    *(int *)((char *)(temp_s0_2) + 4) = (int)((int) (*(int *)((char *)(temp_s0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0_2);
    }
    temp_s0_3 = (void *)(igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_004e7d80[0] == 0) {
        var_v0_5 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_6 = FUN_002eb010(0x10);
            if (var_v0_6 != 0) {
                var_v0_6 = StringPool_Construct(var_v0_6);
            }
            DAT_00586f20[0] = var_v0_6;
        }
        var_v0_5 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004e7d80[0]));
    }
    sp34 = (void *)(var_v0_5);
    igMetaField_SetFieldName(temp_s0_3, &sp34);
    if (sp34 != 0) {
        temp_a1_3 = (int *)((char *)sp34 - 8);
        temp_v0_3 = *(int *)((char *)(sp34) - 4) - 1;
        *(int *)((char *)(sp34) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_3, temp_a1_3);
        }
    }
    *(int *)((char *)(temp_s0_3) + 8) = 8;
    *(int *)((char *)(temp_s0_3) + 56) = FUN_002b9120();
    *(char *)((char *)(temp_s0_3) + 52) = 1;
    igMetaField_FinalizeDescriptor(temp_s0_3);
    ObjectList_AppendRetained(arg0, temp_s0_3);
    *(int *)((char *)(temp_s0_3) + 4) = (int)((int) (*(int *)((char *)(temp_s0_3) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_3) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0_3);
    }
    igMetaObject_EnsureRegistered();
    FUN_002c8f30();
    FUN_002b9200();
}
