int FUN_00303dc0();

int FUN_00303d70(void *arg0) {
    int temp_v0;

    temp_v0 = FUN_00303dc0();
    if (temp_v0 == -1) {
        return 0;
    }
    return *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 16) + (temp_v0 * 4));
}
