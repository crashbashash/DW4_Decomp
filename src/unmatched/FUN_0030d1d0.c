char *FUN_0030d1d0(int *arg0, int arg1) {
    int *t;
    char *p;
    char *r;
    if (arg1 < 0 || arg1 >= (t = (int *)arg0[4])[2] || (p = (char *)t[4]) == 0) {
        r = 0;
    } else {
        r = p + arg1;
        if (arg1 > 0 && r[-1] != 0) r = 0;
    }
    return r;
}
