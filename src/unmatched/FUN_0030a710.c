extern int DAT_00586f20[4];
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int StringChunk_ReleaseHeader(int, int *);
struct SS { char pad8[8]; int f8; char pad[41]; unsigned char f53; char pad54[6]; int f60; };
void FUN_0030a710(struct SS *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_s0;
    int var_v0;
    int *var_s1;
    int temp_a0;
    int temp_s3;

    if (arg0->f53 != 0) {
        var_s1 = (int *)(arg1 + arg0->f8);
        for (var_s0 = 0; var_s0 < arg0->f60; var_s0++) {
            if (DAT_00586f20[0] == 0) {
                var_v0 = FUN_002eb010(0x10);
                if (var_v0 != 0) {
                    var_v0 = StringPool_Construct(var_v0);
                }
                DAT_00586f20[0] = var_v0;
            }
            temp_s3 = StringPool_Intern(DAT_00586f20[0], 0);
            temp_a0 = *var_s1;
            if (temp_a0 != 0) {
                temp_a1 = (int *)(temp_a0 - 8);
                temp_v1 = *(int *)(temp_a0 - 4) - 1;
                *(int *)(temp_a0 - 4) = temp_v1;
                if (temp_v1 == 0) {
                    StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                }
            }
            *var_s1 = temp_s3;
            var_s1 += 1;
        }
    }
}
