void FUN_001ce3d0(void **arg0) {
    void *temp_a0;

    *arg0 = 0;
    temp_a0 = *arg0;
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) + 4) = (int) (*(int *)((char *)(temp_a0) + 4) + 1);
    }
}
