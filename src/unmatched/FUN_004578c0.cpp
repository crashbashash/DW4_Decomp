/* Virtual call on each non-null element except one. */
struct S;
extern "C" void FUN_004578c0(S *arg0, S *arg1);
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(S *); };

struct L { char p[8]; int n; char q[4]; VC **arr; };
struct S { char p[4]; VC *f4; L *f8; };
void FUN_004578c0(S *arg0, S *arg1) {
    int var_s0;
    VC *o;
    for (var_s0 = 0; var_s0 < arg0->f8->n; var_s0++) {
        o = arg0->f8->arr[var_s0];
        if (o != 0 && o != arg1->f4) {
            o->vX(arg1);
        }
    }
}
