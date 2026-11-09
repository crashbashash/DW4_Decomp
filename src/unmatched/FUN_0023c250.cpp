typedef struct Rc { int vt; int refs; } Rc;
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int); };
typedef struct Inst { int pad[5]; Rc *f20; } Inst;
extern "C" {
Rc *FUN_002c37e0(int);
Rc *FUN_002397a0(int);
int FUN_002d8fe0(Rc *, int);
int FUN_002d8310(Rc *, Rc *);
int igObject_Destroy(Rc *);
}
/* Selects the constructor that takes over the factory's reference. */
struct AdoptReference { };
struct RcRef { Rc *p; RcRef(Rc *o, AdoptReference) : p(o) {} ~RcRef() { Rc *o = p; if (o) { o->refs = o->refs - 1; if ((o->refs & 0x7FFFFF) == 0) igObject_Destroy(o); } } Rc *get() const { return p; } };
extern "C" void FUN_0023c250(int *arg0) {    RcRef a(FUN_002c37e0(0), AdoptReference());
    FUN_002d8fe0(a.get(), arg0[13]);
    RcRef b(FUN_002397a0(0), AdoptReference());
    {
    Rc *s1 = (Rc *)arg0[14];
    Inst *s0 = (Inst *)b.get();
    if (s1) s1->refs = s1->refs + 1;
    Rc *t = s0->f20;
    if (t) { t->refs = t->refs - 1; if ((t->refs & 0x7FFFFF) == 0) igObject_Destroy(t); }
    s0->f20 = s1;
    }
    FUN_002d8310(a.get(), b.get());
    ((Obj *)a.get())->vX(arg0[13]);
}
