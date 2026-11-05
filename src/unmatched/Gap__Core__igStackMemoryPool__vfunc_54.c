int Gap__Core__igStackMemoryPool__vfunc_54(int *arg0, int arg1) {
    int a1, a3, a4, v1;
    unsigned short a2;
    if (arg1 == 0) {
        return 0;
    }
    a2 = *(unsigned short *)(arg0 + 28);
    a3 = arg0[33];
    a4 = a2 - 1;
    v1 = a4 & (a2 - (a3 & a4));
    a1 = arg1 + v1;
    if (arg0[34] - a3 < a1) {
        return 0;
    }
    arg0[33] = a3 + a1;
    *(int *)arg0[34] = a1;
    arg0[34] = arg0[34] - 4;
    return a3 + v1;
}
