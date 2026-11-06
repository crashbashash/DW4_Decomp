typedef struct S0 { char pad88[88]; int f58; } S0;
int StringChunk_ReleaseHeader();

void FUN_00156340(S0 *arg0, void **arg1) {
    int *temp_a1;
    int temp_v1;
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = (void *)(*arg1);
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) - 4) = (int)((int) (*(int *)((char *)(temp_a0) - 4) + 1));
    }
    temp_a0_2 = (void *)(arg0->f58);
    if (temp_a0_2 != 0) {
        temp_a1 = (int *)((char *)temp_a0_2 - 8);
        temp_v1 = *(int *)((char *)(temp_a0_2) - 4) - 1;
        *(int *)((char *)(temp_a0_2) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->f58 = (int)((int) *arg1);
}
