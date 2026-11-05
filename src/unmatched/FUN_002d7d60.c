int FUN_002d7d60(void *arg0, int arg1) {
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 44));
    if (temp_v0 != 0) {
        return *(int *)(*(int *)((char *)(temp_v0) + 16) + (arg1 * 4));
    }
    return *(int *)((char *)((*(int *)(*(int *)((char *)(arg0) + 16) + (arg1 * 4)))) + 24);
}
