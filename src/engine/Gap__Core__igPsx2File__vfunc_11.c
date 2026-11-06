int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
void *StringPool_Intern();
extern int DAT_00586f20[4];
extern int DAT_00587330[4];
struct O { char pad[72]; int *s; };
void Gap__Core__igPsx2File__vfunc_11(struct O *arg0) {
    int *temp_a1;
    int temp_s0;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0_2;
    temp_s0 = DAT_00587330[0];
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0_2 = StringPool_Intern(DAT_00586f20[0], temp_s0);
    temp_a0 = arg0->s;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->s = temp_s0_2;
}
