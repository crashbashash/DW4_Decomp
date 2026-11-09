/* The list count is read const so it is reloaded for the increment. */
extern "C" {
int FUN_001db500();
int List_Resize(...);
extern int DAT_0048dae8[4];
}
struct SorterDevice {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void f30(int);
    virtual void f31(int);
};
struct SorterList { int pad[2]; int count; int cap; int *items; };
struct SorterState { char pad[64]; SorterDevice *a; SorterDevice *b; SorterDevice *c; int pad2; SorterList *l80; SorterList *l84; SorterList *l88; };
static inline void setRef(SorterList *l, int i, const int &v) {
    if (l->count != 0 && i >= 0 && i < l->count) { l->items[i] = v; }
}
extern "C" void Gap__Sg__igSorter__vfunc_09(SorterState *o, int arg1) {
    int s3;
    SorterList *s2;
    SorterList *s0;
    SorterList *l;
    if (arg1 == 0) {
        FUN_001db500();
        o->a->f30(0);
        o->b->f30(1);
        o->b->f31(1);
        o->c->f30(0);
        o->c->f31(1);
        o->l80->cap = o->l80->count;
        s2 = o->l84;
        s3 = *(const int *)&s2->count;
        s0 = o->l80;
        if (s3 < s2->cap) {
            s2->count = s2->count + 1;
        } else {
            List_Resize(s2, s3 + 1, 4);
        }
        s2->items[s3] = (int)s0;
        l = o->l88;
        if (l->cap > 0) {
            l->count = 1;
        } else {
            List_Resize(l, 1, 4);
        }
        setRef(o->l88, 0, DAT_0048dae8[0]);
    }
}
