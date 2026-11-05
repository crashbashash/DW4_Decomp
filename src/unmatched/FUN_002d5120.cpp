class VC132 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void vX(int); };
extern "C" {
struct B { char pad[8]; int cnt; char pad2[4]; VC132 **arr; };
struct A { char pad[52]; struct B *b; };
void FUN_002d5120(A *a, int x) {
    int i;
    for (i = 0; i < a->b->cnt; i++) {
        a->b->arr[i]->vX(x);
    }
}
}
