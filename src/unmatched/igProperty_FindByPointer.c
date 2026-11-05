int igProperty_FindByPointer(void *arg0, void *arg1, int arg2) {
    int temp_v0;
    int n;
    int i;

    n = *(int *)((char *)(arg0) + 8);
    if (arg1 == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        temp_v0 = *(int *)(*(int *)((char *)(arg0) + 16) + (i * 4));
        if (temp_v0 != 0) {
            int w = *(int *)(temp_v0 + *(int *)((char *)(arg1) + 8));
            if (w == arg2) {
                return temp_v0;
            }
        }
    }
    return 0;
}
