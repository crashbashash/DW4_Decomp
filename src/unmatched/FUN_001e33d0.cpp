extern "C" {
int FUN_001925f0(...);
int FUN_001e33d0(void **arg0, int arg1);
}
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
int FUN_001e33d0(void **arg0, int arg1) {
    int sp30[16];
    int temp_s0;

    temp_s0 = ((DW4VC_96_1 *)(arg0))->vX((int)(sp30)) & 0xFF;
    FUN_001925f0(arg1, sp30);
    return temp_s0;
}
