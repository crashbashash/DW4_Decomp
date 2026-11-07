struct Rc { int w0; int refs; int f8; };
struct Ent { char pad[12]; char *name; };
struct Lst { char pad[8]; Ent **arr; unsigned int count; };
struct Obj { char pad[40]; Lst *lst; };
class A { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual Obj *getObj(); };
class B { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void put(char *); };
extern "C" Rc *FUN_002b9500(int);
extern "C" int FUN_0030b3c0(Rc *, char *);
extern "C" int FUN_0022c150(int, B *, Rc *, int, Ent *, A *);
extern "C" int igObject_Destroy(Rc *);
extern char DAT_004e7ea8[16];
extern "C" int FUN_0022c7f0(A *arg0, int arg1, B *arg2, int arg3) {
    bool found;
    Rc *volatile spBC;
    Lst *l;
    unsigned int n;
    unsigned int i;
    volatile char spB8[4];
    Rc *t;
    spB8[0] = 0;
    char *nm;
    Ent *e;
    spBC = FUN_002b9500(0);
    l = arg0->getObj()->lst;
    found = 0;
    i = 0;
    n = l->count;
    for (; i < n; i++) {
        e = l->arr[i];
        nm = e->name;
        FUN_0030b3c0(spBC, nm);
        if (FUN_0022c150(arg1, arg2, spBC, arg3, e, arg0) != 0) {
            found = 1;
        } else if (*nm == 0x5f) {
            FUN_0030b3c0(spBC, e->name + 1);
            if (0 != FUN_0022c150(arg1, arg2, spBC, arg3, e, arg0)) found = 1;
        }
    }
    if (found) arg2->put(DAT_004e7ea8);
    t = spBC;
    if (t) {
        t->refs -= 1;
        if (0 == (t->refs & 0x7fffff)) igObject_Destroy(t);
    }
    return 1;
}
