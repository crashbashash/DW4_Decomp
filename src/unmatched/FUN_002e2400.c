void FUN_002e2400(void *arg0, int arg1, int arg2) {
    int t, idx;
    char *p;
    if (arg1 < 0x10) {
        t = arg1 * 2;
        *(int *)((char *)(arg0) + 80) = (1 << t) | (*(int *)((char *)(arg0) + 80) & ~(3 << t));
        idx = arg1 << 2; p = (char *)idx + (int)arg0; *(int *)(p + 84) = arg2;
    }
}
