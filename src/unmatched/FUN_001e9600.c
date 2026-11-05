int FUN_001e90c0();
int FUN_001e91c0();
int FUN_001e9320();
int FUN_001e9450();
int FUN_001e9550();
extern long long DAT_00562d38[4];
long long FUN_001e9600(long long arg0, int arg1, int arg2) {
    if (arg1 == 4) {
        DAT_00562d38[0] += (long long) (arg0 << 0x20) >> 0x20;
    }
    switch (arg1) {
    case 1:
        FUN_001e9550(arg0, arg2);
        break;
    case 2:
        FUN_001e9450(arg0, arg2);
        break;
    case 3:
        FUN_001e9320(arg0, arg2);
        break;
    case 4:
        FUN_001e91c0(arg0, arg2);
        break;
    default:
        FUN_001e90c0(arg0);
        break;
    }
    return arg0;
}
