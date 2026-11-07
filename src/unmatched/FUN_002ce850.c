int FUN_002eb010();
int Memory_GetAllocatorBySelector();
int ObjectList_AppendRetained();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
void *StringPool_Intern();
int igMetaField_FinalizeDescriptor();
int igMetaField_SetFieldName();
int igObject_Destroy();
void *igUnsignedIntMetaField_Create();
extern int DAT_004f8cc0[4];
extern int DAT_00586f20[4];
extern int DAT_00587040[4];
void FUN_002ce850(int arg0) {
    void *sp3C;
    int *temp_a1;
    int temp_v0;
    int var_v0_2;
    void *temp_s0;
    void *var_v0;

    temp_s0 = (void *)(igUnsignedIntMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_004f8cc0[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004f8cc0[0]));
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
    igMetaField_FinalizeDescriptor(temp_s0);
    ObjectList_AppendRetained(arg0, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}
