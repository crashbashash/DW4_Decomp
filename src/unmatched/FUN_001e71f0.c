int FUN_001e6d80();
int FUN_001e6f10();
int FUN_00306910();
int StringChunk_ReleaseHeader();
extern int DAT_004e4ae8[4];
extern int DAT_004e4b00[4];
int FUN_001e71f0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    void *sp6C;
    void *sp68;
    int *temp_a1;
    int *temp_a1_2;
    int *temp_a1_3;
    int *temp_a1_4;
    int temp_s0;
    int temp_v0;
    int temp_v0_2;
    int temp_v0_3;
    int temp_v0_4;

    sp6C = (void *)(0);
    FUN_001e6f10(&sp68, arg4, &DAT_004e4ae8[0]);
    if (FUN_00306910(arg0, arg1, arg2, &sp6C, sp68, arg5) != 0) {
        temp_s0 = FUN_001e6d80(sp6C, arg3, &DAT_004e4b00[0]) & 0xFF;
        if (sp68 != 0) {
            temp_a1 = (int *)((char *)sp68 - 8);
            temp_v0 = *(int *)((char *)(sp68) - 4) - 1;
            *(int *)((char *)(sp68) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
        if (sp6C != 0) {
            temp_a1_2 = (int *)((char *)sp6C - 8);
            temp_v0_2 = *(int *)((char *)(sp6C) - 4) - 1;
            *(int *)((char *)(sp6C) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
        return temp_s0;
    }
    if (sp68 != 0) {
        temp_a1_3 = (int *)((char *)sp68 - 8);
        temp_v0_3 = *(int *)((char *)(sp68) - 4) - 1;
        *(int *)((char *)(sp68) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_3, temp_a1_3);
        }
    }
    if (sp6C != 0) {
        temp_a1_4 = (int *)((char *)sp6C - 8);
        temp_v0_4 = *(int *)((char *)(sp6C) - 4) - 1;
        *(int *)((char *)(sp6C) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_4, temp_a1_4);
        }
    }
    return 0;
}
