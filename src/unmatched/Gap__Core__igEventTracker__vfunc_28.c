extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void Gap__Core__igEventTracker__vfunc_28(int *arg0, char *arg1, char *arg2, int *arg3) {
    int t;
    int sh;
    int acc;
    int c;
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
    *arg3 = acc;
    if (*arg3 >= 0x20) {
        *arg0 = DAT_004fb418[0];
    } else {
        *arg0 = DAT_004fb410[0];
    }
}
