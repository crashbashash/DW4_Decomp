void FUN_001b23b0(int *arg0, int *arg1) {
    int *p;
    *arg0 = arg1[3];
    p = (int *)*arg0;
    if (p != 0) {
        p[1] = p[1] + 1;
    }
}
