extern "C" {
int StringChunk_ReleaseHeader(int, int *);

void FUN_00406fa0(void **arg0) {
    int *temp_a1;
    int temp_v1;
    void *temp_a0;

    temp_a0 = (void *)(*arg0);
    if (temp_a0 != 0) {
        temp_a1 = (int *)((char *)temp_a0 - 8);
        temp_v1 = *(int *)((char *)(temp_a0) - 4) - 1;
        *(int *)((char *)(temp_a0) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
}
}
