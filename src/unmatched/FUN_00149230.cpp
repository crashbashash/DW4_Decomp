/* 0x00149230 - 184 bytes. Byte table lookup scaled by 1/255, else a virtual query turned into 1.0/0.0 for the callee; C++ unit (t9 virtual call), float result variable, default compiler with -O3,p. The two div.s hazard nops come from the compiler, the explicit asm nops reproduce them here. */
extern "C" {
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(int); };
int FUN_001480a0(O *, int);
float FUN_00230e50(long long);
float FUN_00149230(O *arg0, int arg1);
float FUN_00149230(O *arg0, int arg1) {
    int i;
    int t;
    unsigned v;
    long long d;
    unsigned char *p;
    float r;
    i = FUN_001480a0(arg0, arg1);
    if (i >= 0) {
        p = (unsigned char *)(i + (int)arg0);
        v = p[97];
        r = (float)v / 255.0f;
        asm("nop");
        asm("nop");
    } else {
    t = arg0->vX(arg1);
    d = 0;
    if (t != 0) {
        d = (long long)0x3FF00000 << 0x20;
    }
    r = FUN_00230e50(d);
    }
    return r;
}
}
