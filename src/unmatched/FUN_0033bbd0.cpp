class V116 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(void *); };
extern "C" {
struct E { char pad72[72]; V116 *f72; };
struct L { char pad8[8]; int cnt; char pad12[4]; E **arr; };
struct S { char pad16[16]; L *l; };
void FUN_0033bbd0(S *arg0) {
    int i;

    if (arg0->l != 0) {
        for (i = 0; i < arg0->l->cnt; i++) {
            E *e = arg0->l->arr[i];
            e->f72->vX(e);
        }
    }
}
}
