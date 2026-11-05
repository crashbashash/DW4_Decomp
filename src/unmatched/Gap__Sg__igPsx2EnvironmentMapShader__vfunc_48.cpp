extern "C" {
int FUN_001e16a0(...);
int FUN_001e1ac0(...);
int FUN_001e1e70(...);
int FUN_001e22c0(...);
}
class A1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); };
class S { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void v47(A1*); virtual void d48(); virtual void v49(A1*); virtual void v50(); char p[28]; int f32; char p2[12]; unsigned char f48; char p3[3]; int f52; char p4[4]; char f60; char p5[11]; char f72; };
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_48(S *self, A1 *arg1) {
    int v;
    unsigned char fl;
    self->v50();
    self->f60 = 1;
    if (self->f32 != 0) {
        self->v47(arg1);
        self->v49(arg1);
        self->f72 = 1;
        v = arg1->vX(22);
        fl = self->f48;
        if (fl == 0 && v > 2 && self->f52 != 0) {
            FUN_001e22c0(self, arg1);
            return;
        }
        if (self->f52 != 0) {
            FUN_001e1e70(self, arg1);
            return;
        }
        if (fl == 0 && v > 1) {
            FUN_001e16a0(self, arg1);
            return;
        }
        FUN_001e1ac0(self, arg1);
    }
}
