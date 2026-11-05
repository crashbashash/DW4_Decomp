class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void v92(); virtual void v96(); char pad[124]; unsigned char f128; };
struct S20 { char p[20]; int f20; };
struct S8 { char p[8]; int f8; };
struct A { char p[48]; char f48; char p1[3]; C *f52; char p2[12]; C *f68; S20 *f72; S20 *f76; S20 *f80; S20 *f84; S20 *f88; S20 *f92; S20 *f96; char p3[148]; S8 *f248; S8 *f252; char p4[12]; S20 *f268; };
extern "C" {
int FUN_001d9bb0(...);
void Gap__Sg__igCommonTraversal__vfunc_31(A *arg0);
}
void Gap__Sg__igCommonTraversal__vfunc_31(A *arg0) {
    C *temp_a0;

    temp_a0 = arg0->f68;
    if (temp_a0->f128 == 0) {
        FUN_001d9bb0(temp_a0, arg0->f52);
    }
    arg0->f48 = 0;
    arg0->f52->v92();
    arg0->f68->v96();
    arg0->f72->f20 = 0;
    arg0->f80->f20 = 0;
    arg0->f84->f20 = 0;
    arg0->f88->f20 = 0;
    arg0->f268->f20 = 0;
    arg0->f92->f20 = 0;
    arg0->f96->f20 = 0;
    arg0->f76->f20 = 0;
    arg0->f248->f8 = 0;
    arg0->f252->f8 = 0;
}
