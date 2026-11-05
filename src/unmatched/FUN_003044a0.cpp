class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(char *, int, int); };
extern "C" {
int printf(...);
int FUN_0012fce0(...);
int FUN_0012fd08(...);
extern int DAT_004f95a0[4];
extern VC * DAT_005871b0[4];
extern unsigned char GPR_00554998;
extern unsigned char GPR_0055499c;
void FUN_003044a0(int arg0, int arg1);
}
void FUN_003044a0(int arg0, int arg1) {
    char sp10[4096];
    int var_v0;

    if ((DAT_005871b0[0] != 0) && (GPR_00554998 != 0)) {
        var_v0 = FUN_0012fd08(&sp10[0], 0x1000, arg0, arg1);
        if ((var_v0 < 0) || (var_v0 >= 0x1000)) {
            sp10[4095] = 0;
            var_v0 = 0x1000;
        }
        DAT_005871b0[0]->vX(&sp10[0], var_v0, 1);
        if (GPR_0055499c != 0) {
            printf(&DAT_004f95a0[0], &sp10[0]);
        }
    } else if (GPR_0055499c != 0) {
        FUN_0012fce0(arg0, arg1);
    }
}
