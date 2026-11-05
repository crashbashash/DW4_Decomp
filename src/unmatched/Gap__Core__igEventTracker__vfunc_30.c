extern int DAT_004c1ea8[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void Gap__Core__igEventTracker__vfunc_30(int *arg0, char *arg1, char *arg2, int *arg3) {
    int t;
    int sh;
    int acc;
    int c;
    int t2;
    int c2;
    int sh2;
    int acc2;
    int sh3;
    char *p;
    sh = 0;
    acc = 0;
    arg2 = (char *)(*(int *)(*(char **)(arg1 + 80) + 16) + (int)arg2);
    do {
        c = *arg2;
        t = c & 0x7F;
        arg2++;
        t = t << sh;
        c = c & 0x80;
        acc |= t;
        if (c == 0) break;
        sh += 7;
    } while (1);
    if (acc >= 0x20) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    {
    char *q = arg2 + 1;
    c = *arg2;
    if (DAT_004c1ea8[0] < c) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    acc2 = 0;
    sh2 = 0;
    do {
        c2 = *q;
        t2 = c2 & 0x7F;
        q++;
        t2 = t2 << sh2;
        c2 = c2 & 0x80;
        acc2 |= t2;
        if (c2 == 0) break;
        sh2 += 7;
    } while (1);
    if (acc2 & 1) {
        volatile int val;
        val = ((unsigned char)q[0]) | ((((unsigned char)q[1]) << 8) | ((((unsigned char)q[3]) << 24) | (((unsigned char)q[2]) << 16)));
        p = q + 4;
        sh3 = 0;
        *arg3 = 0;
        for (;;) {
            *arg3 |= (*p & 0x7F) << sh3;
            if ((*p++ & 0x80) == 0) break;
            sh3 += 7;
        }
    } else {
        *arg0 = DAT_004fb418[0];
        return;
    }
    *arg0 = DAT_004fb410[0];
    }
}
