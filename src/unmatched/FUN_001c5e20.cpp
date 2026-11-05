class X { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vX(void *); };
struct L { char pad8[8]; unsigned int f8; char pad12[4]; X **f16; };
struct T { char pad28[28]; L *f28; };
extern "C" {
int Gap__Core__igObject__vfunc_08__001d3390(...);
void FUN_001c5e20(T *arg0);
}
void FUN_001c5e20(T *arg0) {
    unsigned int var_s0;
    unsigned int var_s2;
    L *temp_v0;

    temp_v0 = arg0->f28;
    if (temp_v0 != 0) {
        var_s0 = temp_v0->f8;
    } else {
        var_s0 = 0;
    }
    for (var_s2 = 0; var_s2 < var_s0; var_s2++) {
        arg0->f28->f16[var_s2]->vX(arg0);
    }
    Gap__Core__igObject__vfunc_08__001d3390(arg0);
}
