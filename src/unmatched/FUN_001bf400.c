void FUN_001bf400(int arg0, int arg1, long long arg2) {
    unsigned short *p;
    int idx;
    int base;
    arg0 = *(int *)(arg0 + 16);
    idx = arg1 << 1;
    base = *(int *)(arg0 + 16);
    base = base + idx;
    p = (unsigned short *)base;
    *p = 0;
    if (arg2 < 0) {
        arg2 = -arg2;
        *p |= 0x8000;
    }
    *p |= (arg2 >> 0x17) & 0xFFFF;
}
