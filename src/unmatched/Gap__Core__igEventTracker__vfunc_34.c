extern int DAT_004c1ea8[4];
struct Q { int p0; int p1; int count; int p3; signed char *data; };
int Gap__Core__igEventTracker__vfunc_34(int *arg0, int arg1) {
    struct Q *q;
    signed char *p;
    int n;
    int c;

    q = (struct Q *)arg0[20];
    n = q->count;
    if (n < arg1) {
        return -1;
    }
    p = q->data + arg1;
    if ((unsigned int)*p++ >= 0x20U) {
        return -1;
    }
    c = *p;
    if (DAT_004c1ea8[0] < c) {
        return -1;
    }
    arg1 = arg1 + (c + 2);
    if (arg1 >= n) {
        arg1 = -1;
    }
    return arg1;
}
