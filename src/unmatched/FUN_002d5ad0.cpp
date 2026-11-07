class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48();  virtual int vX(int, int, int, int); };
struct E { char pad8[8]; int f8; };
struct L { char pad8[8]; int cnt; char pad12[4]; E **arr; };
struct S { char pad8[8]; int f8; char pad12[40]; L *f34; };
extern "C" int FUN_002d5ad0(S *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" int FUN_002d5ad0(S *arg0, int arg1, int arg2, int arg3, int arg4) {
    VC *temp_a0;
    int var_s7;
    int temp_v0;
    int temp_s6;
    int temp_s5;
    int var_s4;

    var_s7 = 0;
    var_s4 = 0;
    temp_s5 = arg0->f8;
    temp_s6 = arg0->f34->cnt;
    for (; var_s4 < temp_s6; var_s4++) {
        temp_a0 = (VC *)arg0->f34->arr[var_s4];
        temp_v0 = ((E *)temp_a0)->f8;
        var_s7 += temp_a0->vX((arg1 + temp_v0) - temp_s5, (arg2 + temp_v0) - temp_s5, arg3, arg4);
    }
    return var_s7;
}
