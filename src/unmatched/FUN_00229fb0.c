int StringChunk_ReleaseHeader();

void **FUN_00229fb0(void **arg0, void **arg1) {
    int *temp_a1;
    int temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = (void *)(*arg1);
    if (temp_v1 != 0) {
        *(int *)((char *)(temp_v1) - 4) = (int)((int) (*(int *)((char *)(temp_v1) - 4) + 1));
    }
    temp_v1_2 = (void *)(*arg0);
    if (temp_v1_2 != 0) {
        temp_a1 = (int *)((char *)temp_v1_2 - 8);
        temp_v0 = *(int *)((char *)(temp_v1_2) - 4) - 1;
        *(int *)((char *)(temp_v1_2) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *arg0 = *arg1;
    return arg0;
}
