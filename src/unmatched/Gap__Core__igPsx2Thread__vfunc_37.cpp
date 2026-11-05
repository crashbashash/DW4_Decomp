struct R { int v; R() {} R(int x) { v = x; } R(const R &o) : v(o.v) {} };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int v30(); char p4[28]; int f32; int f36; char p40[5]; unsigned char f45; };
extern "C" {
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
int FUN_00300f50(...);
R Gap__Core__igPsx2Thread__vfunc_37(C *arg1, int arg2, int arg3) {
    if (arg1->v30() == 0) {
        if (arg2 & 0xF) {
            return R(DAT_004fb418[0]);
        }
        if (arg1->f45 == 0) {
            int a1 = arg1->f32;
            if (a1 != 0) {
                FUN_00300f50(arg1, a1);
            }
        }
        arg1->f32 = arg2;
        arg1->f45 = 1;
        arg1->f36 = arg3;
        return R(DAT_004fb410[0]);
    }
    return R(DAT_004fb418[0]);
}
}
