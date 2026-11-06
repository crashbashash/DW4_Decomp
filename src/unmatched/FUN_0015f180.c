int Memory_FreeBuffer();

void FUN_0015f180(void *arg0) {
    int temp_a0;
    int temp_a0_2;
    int temp_a0_3;

    temp_a0 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 64);
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 64) = 0;
    }
    temp_a0_2 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 60);
    if (temp_a0_2 != 0) {
        Memory_FreeBuffer(temp_a0_2);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 60) = 0;
    }
    temp_a0_3 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 76);
    if (temp_a0_3 != 0) {
        Memory_FreeBuffer(temp_a0_3);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 76) = 0;
    }
}
