struct R { char pad4[4]; int refs; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();  virtual int vX(R **); };
struct L { char pad8[8]; int cnt; char pad12[4]; R **arr; };
struct S { char pad16[16]; VC *f10; L *f14; };
extern "C" {
int igObject_Destroy(...);
void Gap__Core__igPluginHelper__vfunc_10(S *arg0);
}
void Gap__Core__igPluginHelper__vfunc_10(S *arg0) {
    int var_s0; int temp_s1;
    R *sp4C;

    temp_s1 = arg0->f14->cnt;
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        sp4C = arg0->f14->arr[var_s0];
        if (sp4C != 0) {
            sp4C->refs = sp4C->refs + 1;
        }
        arg0->f10->vX(&sp4C);
        if (sp4C != 0) {
            sp4C->refs = sp4C->refs - 1;
            if ((sp4C->refs & 0x7fffff) == 0) {
                igObject_Destroy(sp4C);
            }
        }
    }
}
