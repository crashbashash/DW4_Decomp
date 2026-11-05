class V88 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct L { char pad[8]; V88 **items; int count; };
struct A { char pad[36]; V88 *f24; int f28; };
extern "C" {
L *FUN_002fc250(...);
void FUN_002eed00(A *arg0, V88 *arg1);
}
void FUN_002eed00(A *arg0, V88 *arg1) {
    int n;
    int i;
    L *l;
    V88 *o;
    int r;

    arg0->f24 = arg1;
    if (arg1 != 0) {
        l = FUN_002fc250();
        n = l->count;
        for (i = 0; i < n; i++) {
            o = l->items[i];
            r = o->vX();
            if (r == arg1->vX()) {
                arg0->f28 = i;
                return;
            }
        }
    }
}
