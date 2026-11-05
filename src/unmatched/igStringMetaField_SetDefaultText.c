int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
void *StringPool_Intern();
extern int DAT_00586f20[4];
void igStringMetaField_SetDefaultText(int *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    void **temp_s1;
    void *temp_a0;
    void *temp_s0;

    temp_s1 = (void **)arg0[8];
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = (void *)(StringPool_Intern(DAT_00586f20[0], arg1));
    temp_a0 = (void *)(*temp_s1);
    if (temp_a0 != 0) {
        temp_a1 = (int *)((char *)temp_a0 - 8);
        temp_v1 = *(int *)((char *)(temp_a0) - 4) - 1;
        *(int *)((char *)(temp_a0) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *temp_s1 = temp_s0;
}
