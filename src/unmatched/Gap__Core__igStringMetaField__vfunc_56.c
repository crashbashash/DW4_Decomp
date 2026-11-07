int strlen();
int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
void *StringPool_Intern();
extern int DAT_00586f20[4];
void Gap__Core__igStringMetaField__vfunc_56(int arg0, int a1, int arg2) {
    int *temp_a1;
    int temp_v0;
    int var_v0;
    void *temp_v1;
    void **arg1;
    void *temp_s0;

    arg1 = (void **)a1;
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = (void *)(StringPool_Intern(DAT_00586f20[0], arg2));
    temp_v1 = (void *)(*arg1);
    if (temp_v1 != 0) {
        temp_a1 = (int *)((char *)temp_v1 - 8);
        temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
        *(int *)((char *)(temp_v1) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *arg1 = temp_s0;
    strlen(arg2);
}
