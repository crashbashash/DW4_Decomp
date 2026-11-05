class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); char pad4[48]; int f52; char pad56[180]; int f236; };
struct A { char pad20[20]; unsigned int f20; };
extern "C" {
int FUN_001b1030(...);
int FUN_001b1100(...);
int FUN_001b9530(...);
int FUN_001d1760(...);
int FUN_001b7ce0(C *arg0, A *arg1);
}
int FUN_001b7ce0(C *arg0, A *arg1) {
    int temp_s0;

    if (arg1->f20 & 0x20) {
        return 0;
    }
    FUN_001d1760(arg1, arg0->vX());
    FUN_001b1030(arg0->f52, arg0->f236);
    temp_s0 = FUN_001b9530(arg0, arg1);
    FUN_001b1100(arg0->f52, arg0->f236);
    return temp_s0;
}
