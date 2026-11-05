int FUN_00100610();
int FUN_00244e70();
extern int DAT_0056dea0[4];
extern int DAT_0056deb0[4];
int *FUN_002444c0(int *arg0, long long arg1) {
    if (arg0 != 0) {
        if (arg0 != 0) {
            DAT_0056deb0[0] -= 1;
            if (*arg0 != DAT_0056dea0[0]) {
                FUN_00244e70();
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
