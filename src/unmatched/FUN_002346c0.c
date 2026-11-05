int FUN_002345b0();
int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
void *StringPool_Intern();
extern int DAT_00586f20[4];
int FUN_002346c0(int arg0, int arg1, int arg2, void **arg3) {
    int sp3C;
    int str;
    int *temp_a1;
    int temp_v0;
    int var_v0;
    void *temp_s1;
    void *temp_v1;

    sp3C = 0;
    if (FUN_002345b0(arg0, arg1, arg2, &sp3C) != 0) {
        str = sp3C;
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        temp_s1 = (void *)(StringPool_Intern(DAT_00586f20[0], str));
        temp_v1 = (void *)(*arg3);
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        *arg3 = temp_s1;
        return 1;
    }
    return 0;
}

