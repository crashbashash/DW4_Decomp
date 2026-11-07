int FUN_001abc20(int *arg0, int arg1) {
    int r;
    int *t;
    unsigned int idx;
    int *bits;

    t = (int *)arg0[6];
    idx = arg1 * 2;
    if (t == 0) {
        return -1;
    }
    bits = (int *)t[4];
    r = 0;
    if ((1 << (idx & 0x1F)) & bits[idx >> 5]) {
        r |= 1;
    }
    idx = idx + 1;
    if ((1 << (idx & 0x1F)) & bits[idx >> 5]) {
        r |= 2;
    }
    return r - 1;
}
