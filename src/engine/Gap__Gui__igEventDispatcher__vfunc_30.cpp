class X { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int, int); };
struct L2 { char pad8[8]; int f8; char pad12[4]; X **f16; };
struct L1 { char pad8[8]; L2 *f8; };
struct T { char pad12[12]; L1 *f12; };
extern "C" {
void Gap__Gui__igEventDispatcher__vfunc_30(T *arg0, int arg1, int arg2, int arg3);
}
void Gap__Gui__igEventDispatcher__vfunc_30(T *arg0, int arg1, int arg2, int arg3) {
    int temp_s1;
    int var_s0;

    temp_s1 = arg0->f12->f8->f8;
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        if (arg0->f12->f8->f16[var_s0]->vX(arg2, arg3) & 0xFF) {
            break;
        }
    }
}
