class V112 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(); };
extern "C" {
struct L { char pad8[8]; unsigned int cnt; char pad12[4]; V112 **arr; };
struct S { char pad32[32]; L *l; };
void Gap__Sg__igAttrSet__vfunc_31(S *arg0) {
    unsigned int n;
    unsigned int i;

    n = arg0->l->cnt;
    for (i = 0; i < n; i++) {
        arg0->l->arr[i]->vX();
    }
}
}
