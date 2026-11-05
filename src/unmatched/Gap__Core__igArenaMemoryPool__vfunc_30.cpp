struct SR { int w; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual SR v136(int); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void v204(); virtual void d50(); virtual void d51(); virtual int v216(int); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void v264(int); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69();
 char p4[112]; unsigned char f116; char p5[19]; long long f136; char p6[24]; int f168; char p7[20]; int f192; int f196; };
extern "C" {
void Gap__Core__igArenaMemoryPool__vfunc_30(O *arg0);
void Gap__Core__igArenaMemoryPool__vfunc_30(O *arg0) {
    SR sp2C;
    if (arg0->f116 == 0) {
        arg0->v204();
        arg0->f136 = 0;
        arg0->f116 = 1;
        arg0->f196 = 0;
        if (arg0->f192 & 8) {
            sp2C = arg0->v136(1);
        }
        if (arg0->f168 != 0) {
            arg0->v264(arg0->v216(0x10));
        }
    }
}
}
