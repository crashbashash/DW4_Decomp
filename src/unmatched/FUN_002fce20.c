int FUN_002eb010();
int StringPool_Construct();
int StringPool_Intern();
extern int DAT_00586f20[4];
void FUN_002fce20(int *arg0, void *arg1) {
    int temp_s0;
    int var_v0;
    int var_v1;

    temp_s0 = *(int *)((char *)(arg1) + 12);
    if (temp_s0 == 0) {
        var_v1 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        var_v1 = StringPool_Intern(DAT_00586f20[0], temp_s0);
    }
    *arg0 = var_v1;
}
