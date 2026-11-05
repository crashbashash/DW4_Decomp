void ***FUN_002e2fb0();
int FUN_002eb010();
int Memory_FreeBuffer();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
void *StringPool_Intern();
extern int DAT_00586f20[4];
void FUN_002e3280(int arg0) {
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0;
    int temp_v1_2;
    int var_v0;
    void **temp_s0;
    void **temp_s1;
    void *temp_a0;
    void *temp_s0_2;
    void *temp_v1;

    if (arg0 == 0) {
        temp_s0 = (void **)(*FUN_002e2fb0());
        if (temp_s0 != 0) {
            if (temp_s0 != 0) {
                temp_v1 = (void *)(*temp_s0);
                if (temp_v1 != 0) {
                    temp_a1 = (int *)((char *)temp_v1 - 8);
                    temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
                    *(int *)((char *)(temp_v1) - 4) = temp_v0;
                    if (temp_v0 == 0) {
                        StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                    }
                }
            }
            Memory_FreeBuffer(temp_s0);
        }
    } else {
        temp_s1 = (void **)(*FUN_002e2fb0());
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        temp_s0_2 = (void *)(StringPool_Intern(DAT_00586f20[0], arg0));
        temp_a0 = (void *)(*temp_s1);
        if (temp_a0 != 0) {
            temp_a1_2 = (int *)((char *)temp_a0 - 8);
            temp_v1_2 = *(int *)((char *)(temp_a0) - 4) - 1;
            *(int *)((char *)(temp_a0) - 4) = temp_v1_2;
            if (temp_v1_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
        *temp_s1 = temp_s0_2;
    }
}
