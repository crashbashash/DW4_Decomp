extern "C" {
int __dl__FPv(int **);
extern int DAT_00522480[4];
extern int DAT_005224a0[4];
int **FUN_00101590(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_005224a0[0];
        if (arg0 != 0) {
            *arg0 = &DAT_00522480[0];
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}
}
