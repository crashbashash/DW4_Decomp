/* 0x002e3d30 — FUN_002e3d30. Hand-retyped from the m2c draft, verified byte-identical to retail by tools/verify.py. */
int strlen();
int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
void *StringPool_Intern();
int igStrCmp();
extern int DAT_004f7910[4];
extern int DAT_00586f20[4];
void FUN_002e3d30(int *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_s0;
    int temp_s1;
    int var_v0;
    int temp_a0_2;
    void *temp_a0;
    void *temp_a0_3;
    void *temp_s0;

    temp_a0 = (void *)(arg0[5]);
    if ((temp_a0 == 0) || (igStrCmp(temp_a0, &DAT_004f7910[0]) == 0)) {
        temp_s1 = ((int *)arg0[26])[3];
        var_s0 = strlen(temp_s1) - 1;
        while (var_s0 > 0 && (temp_a0_2 = *(char *)((temp_s1 + var_s0) - 1)) != 0x2F && temp_a0_2 != 0x5C) {
            var_s0 -= 1;
        }
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        temp_s0 = (void *)(StringPool_Intern(DAT_00586f20[0], temp_s1 + var_s0));
        temp_a0_3 = (void *)(arg0[5]);
        if (temp_a0_3 != 0) {
            temp_a1 = (int *)((char *)temp_a0_3 - 8);
            temp_v1 = *(int *)((char *)(temp_a0_3) - 4) - 1;
            *(int *)((char *)(temp_a0_3) - 4) = temp_v1;
            if (temp_v1 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        arg0[5] = (int)(temp_s0);
    }
}
