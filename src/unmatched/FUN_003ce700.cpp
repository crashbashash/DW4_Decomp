extern "C" {
int FUN_003cdef0(int *, int, int, int, int);
int FUN_003ce500(int *, int *, int, int, int);
extern int DAT_004cc69c[4];
extern int DAT_005159a0[4];
void FUN_003ce700(int *arg0) {
    int i;
    int t;

    FUN_003ce500(arg0, &DAT_005159a0[0], DAT_004cc69c[arg0[4] * 4], 0, 0);
    i = 0;
    do {
        t = i + arg0[5] * 4;
        FUN_003cdef0(arg0, 0, t, 0, 0);
        FUN_003cdef0(arg0, 2, t, 0, 0);
        if (i == 0) {
            FUN_003cdef0(arg0, 1, t / 4, 0, 0);
        }
        i += 1;
    } while (i < 4);
}
}
