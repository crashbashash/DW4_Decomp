struct R { int v; R(int x) { v = x; } int get() { return v; } };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();  virtual R vX(int, int*); };
extern "C" {
int igAllocator_ResolveEncodedIndex(int);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern O *DAT_00586f68[4];
R FUN_002f0180(int arg1, int *arg2);
}
R FUN_002f0180(int arg1, int *arg2) {
    int sp3C;
    O *o = DAT_00586f68[0];
    if (o != 0) {
        int x = o->vX(arg1, &sp3C).get(); if (x == DAT_004fb410[0]) {
            *arg2 = igAllocator_ResolveEncodedIndex(sp3C);
            if (*arg2 != 0) {
                return R(DAT_004fb410[0]);
            }
        }
    }
    *arg2 = 0;
    return R(DAT_004fb418[0]);
}
