extern "C" {
int __dl__FPv();
extern int DAT_00522480[4];
int **FUN_00100670(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_00522480[0];
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            __dl__FPv();
        }
    }
    return arg0;
}
}
