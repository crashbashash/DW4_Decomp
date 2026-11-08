float dptofp();
int FUN_00234560(int, int, int, long long *);

int FUN_00234810(int arg0, int arg1, int arg2, float *arg3) {
    long long sp28;

    if (FUN_00234560(arg0, arg1, arg2, &sp28) != 0) {
        *arg3 = dptofp(sp28);
        return 1;
    }
    return 0;
}
