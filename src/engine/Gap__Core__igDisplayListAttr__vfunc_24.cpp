struct S;
extern "C" void Gap__Core__igDisplayListAttr__vfunc_24(S *arg0, int arg1);
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int); };

struct L { char p[8]; int n; char q[4]; VC **a; };
struct S { char p[12]; L *f12; };
void Gap__Core__igDisplayListAttr__vfunc_24(S *arg0, int arg1) {
    L *temp_v1 = arg0->f12;
    VC **var_s1 = temp_v1->a;
    VC **temp_s0 = var_s1 + temp_v1->n;
    while (var_s1 < temp_s0) {
        (*var_s1)->vX(arg1);
        var_s1 += 1;
    }
}
