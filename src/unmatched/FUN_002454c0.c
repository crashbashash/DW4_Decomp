void FUN_002454c0(void *arg0, int arg1, int arg2, int arg3) {
    char *p;
    unsigned int h;
    void *n;
    void **slot;
    h = *(unsigned int *)arg0;
    arg1 = arg1 + (((arg2 - 1) & (h ^ (h >> arg3))) * 4);
    slot = (void **)arg1;
    *(int *)((char *)arg0 + 4) = (int)*slot;
    n = *slot;
    if (n != 0) {
        p = (char *)arg0;
        if (arg0 != 0) p -= 0xC;
        *(void **)((char *)n + 20) = (void *)p;
    }
    *(int *)((char *)arg0 + 8) = 0;
    *slot = arg0 ? (char *)arg0 - 0xC : arg0;
}
