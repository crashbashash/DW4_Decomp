int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
int StringPool_Intern();
extern int DAT_00586f20[4];

typedef struct A { char pad[20]; int *f20; } A;

void FUN_002d8fe0(A *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0;

    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = (int *)StringPool_Intern(DAT_00586f20[0], arg1);
    temp_a0 = arg0->f20;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->f20 = temp_s0;
}
