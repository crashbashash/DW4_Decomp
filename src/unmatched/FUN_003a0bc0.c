void FUN_003a0bc0(int arg0, void *arg1, void *arg2, int arg3, int arg4, float fparg0) {
    int temp_a0;
    int temp_v1;

    temp_a0 = *(int *)(*(int *)((char *)(*(int *)((char *)(arg1) + 92)) + 16) + (arg4 * 4));
    if (temp_a0 != -1) {
        temp_v1 = *(int *)((char *)(arg2) + 8);
        if ((temp_v1 != 0) && (temp_a0 >= 0) && (temp_a0 < temp_v1)) {
            *(float *)(*(int *)((char *)(arg2) + 16) + (temp_a0 * 4)) = fparg0;
        }
    }
}
