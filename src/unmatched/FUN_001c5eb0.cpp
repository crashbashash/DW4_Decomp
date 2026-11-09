extern "C" {
int FUN_001c6110(...);
int List_RemoveWordAt(...);
int igObject_Destroy(...);
}
struct S;
struct Obj {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void vX(S *);
    int refs; int p8; int p12; int p16; int f20;
};
struct List { int p0, p4; int n; int p12; Obj **data; };
struct S { char pad[28]; List * list; List *getList() const { return list; } };
struct Ref {
    Obj *p;
    Ref() { p = 0; }
    Ref(Obj *o) { p = o; if (p) p->refs++; }
    Ref(const Ref &r) { p = r.p; if (p) p->refs++; }
    ~Ref() {
        Obj *o = p;
        if (o) {
            --o->refs;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) igObject_Destroy(o);
        }
    }
};
extern "C" Ref FUN_001c5eb0(S *host, int idx) {
    List *l0 = host->getList();
    int n = l0 ? l0->n : 0;
    if (idx < n) {
        Ref obj(host->list->data[idx]);
        obj.p->vX(host);
        List *l = host->list;
        Obj *e = l->data[idx];
        if (e) {
            --e->refs;
            if (((unsigned long long)(long long)e->refs & 0x7fffffULL) == 0) igObject_Destroy(e);
        }
        List_RemoveWordAt(l, idx);
        l->data[l->n] = 0;
        FUN_001c6110(host, obj.p->f20);
        return obj;
    }
    return Ref(0);
}
