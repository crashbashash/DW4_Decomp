extern "C" {
extern int DAT_004fb410[4];
int FUN_002d9130(int *arg0);
}
struct SR { int w0; };
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual SR vX(int); };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual SR vX(); };
int FUN_002d9130(int *arg0) {
    SR a;
    SR b;
    int v;

    if (arg0[17] == 0) {
        v = arg0[13] + 1;
        arg0[13] = v;
        return v;
    }
    a = ((A *)arg0[17])->vX(1);
    v = arg0[13];
    if (a.w0 == DAT_004fb410[0]) {
        v += 1;
        arg0[13] = v;
        b = ((B *)arg0[17])->vX();
    }
    return v;
}
