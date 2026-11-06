void FUN_002ace60(void *arg0, int arg1, int arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 13864));
    if (temp_v1 != 0) {
        if (*(int *)((char *)(temp_v1) + 3512) < 0) {
            *(int *)((char *)(temp_v1) + 3512) = arg1;
        }
        if (*(int *)((char *)(temp_v1) + 3516) < 0) {
            *(int *)((char *)(temp_v1) + 3516) = arg2;
        }
    }
}
