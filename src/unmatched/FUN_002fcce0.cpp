class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vB(); virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual int vC(int, int, int); };
extern "C" {
int FUN_002fcce0(VC *arg0, int arg1, int arg2, int arg3, int arg4) {
    int r;
    int s2 = arg1;
    int s1 = arg2;
    int i = 0;
    for (; i < arg3; i++) {
        r = arg0->vC(s1, s2, arg4);
        if (r != 0) {
            s2 = r + s2;
            s1 += arg0->vB();
        } else {
            return 0;
        }
    }
    return s2 - arg1;
}
}
