extern "C" {
int List_Reserve(...);
int List_Resize(...);
}
struct L { int p0; int p1; int count; int cap; int *data; };
class D { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void vf(); int p1; int n; int p3; L *list; };
extern "C" void Gap__Core__igMemoryDictionary__vfunc_25(D *arg0) {
    int a;
    int b;
    L *l;

    a = arg0->n * 2;
    l = arg0->list;
    if (a >= l->count) {
        List_Reserve(l, a, 4);
    }
    b = arg0->n * 2;
    l = arg0->list;
    if (b >= 0) {
        if (b <= l->cap) {
            l->count = b;
        } else {
            List_Resize(l, b, 4);
        }
    }
    arg0->vf();
}
