extern "C" {
int FUN_00100610(int **);
extern int DAT_00522480[4];
extern int DAT_005224a0[4];
int **FUN_00101590(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_005224a0[0];
        if (arg0 != 0) {
            *arg0 = &DAT_00522480[0];
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
}
