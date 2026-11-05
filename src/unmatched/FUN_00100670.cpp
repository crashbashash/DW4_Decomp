extern "C" {
int FUN_00100610();
extern int DAT_00522480[4];
int **FUN_00100670(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_00522480[0];
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            FUN_00100610();
        }
    }
    return arg0;
}
}
