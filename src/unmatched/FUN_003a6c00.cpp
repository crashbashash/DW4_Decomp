extern "C" {
int FUN_00332290(int, int);
int FUN_00332340(int, unsigned char);
struct S { char pad[8]; int f8; char pad2[4]; int f16; };
int FUN_003a6c00(S *arg0, int arg1) {
    unsigned char b = 0;
    int t = arg0->f8;
    if (t != 0) {
        if (arg0->f16 == 1) b = 1;
    }
    if (b) { FUN_00332340(t, b); return FUN_00332290(arg0->f8, arg1); }
    return 0;
}
}
