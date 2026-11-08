int FUN_0010b310(int, int *);
extern char DAT_00555a90[];
int sceDeci2Open(unsigned short a0, int a1, int a2) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = (int)DAT_00555a90 | 0x20000000;
    return FUN_0010b310(1, args);
}
