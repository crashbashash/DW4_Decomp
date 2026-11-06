int StringList_AppendRetained();
int StringPool_Construct();
void *StringPool_Intern();
int FUN_002eb010();
int StringChunk_ReleaseHeader();
extern int DAT_00586f20[4];
void FUN_002d78e0(void *arg0, int arg1) {
    void *sp3C;
    int *temp_a1;
    int temp_v1;
    int var_v0_2;
    void *var_v0;

    if (arg1 == 0) {
        var_v0 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(DAT_00586f20[0], arg1));
    }
    sp3C = (void *)(var_v0);
    StringList_AppendRetained(*(int *)((char *)(arg0) + 20), &sp3C);
    if (sp3C != 0) {
        temp_a1 = (int *)((char *)sp3C - 8);
        temp_v1 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
}
