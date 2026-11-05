class VC92 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); };
class VC96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int); };
extern "C" {
struct L { char pad[8]; int cnt; char pad2[4]; int *arr; };
struct A { char pad[16]; VC92 **arr; char pad2[20]; int f40; struct L *l; };
void FUN_002d7da0(A *a, int i, int x) {
    if (a->l != 0 && a->f40 != 0) {
        VC92 *o = a->arr[i];
        o->vX(x);
        ((VC96 *)o)->vX(x);
        {
            struct L *l = a->l;
            if (l->cnt != 0 && i >= 0 && i < l->cnt) l->arr[i] = x;
        }
    } else {
        a->arr[i]->vX(x);
    }
}
}
