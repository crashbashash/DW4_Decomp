void FUN_00337480(void *arg0, unsigned long long arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    unsigned long long m;
    int *p = (int *)arg0;
    p[0] = (arg6 << 0xF) | arg7;
    p[1] = (arg2 << 0x1C) | ((arg3 << 0x1A) | ((arg5 << 0xE) | (arg4 << 0xF)));
    m = 0xFFFF;
    m = (m << 16) | 0xFFFF;
    p[2] = (int)(arg1 & m);
    p[3] = (int)(arg1 >> 32);
}
