typedef struct Rc { int vt; int refs; } Rc;
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int); };
typedef struct Inst { int pad[5]; Rc *f20; } Inst;
extern "C" {
Rc *FUN_002c37e0(int);
Rc *FUN_002397a0(int);
int FUN_002d8fe0(Rc *, int);
int FUN_002d8310(Rc *, Rc *);
int igObject_Destroy(Rc *);
void FUN_0023c250(int *arg0);
void FUN_0023c250(int *arg0) {
    Rc * volatile sp4C;
    Rc * volatile sp48;
    volatile char sp44[4];
    volatile char sp40[4];
    Rc *t, *s1;
    Inst *s0;
    sp44[0] = 0;
    sp4C = FUN_002c37e0(0);
    FUN_002d8fe0(sp4C, arg0[13]);
    sp40[0] = 0;
    sp48 = (Rc *)FUN_002397a0(0);
    s1 = (Rc *)arg0[14];
    s0 = (Inst *)sp48;
    if (s1) s1->refs = s1->refs + 1;
    t = s0->f20;
    if (t) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t);
    }
    s0->f20 = s1;
    { Rc *b = sp48; FUN_002d8310(sp4C, b); }
    ((Obj *)sp4C)->vX(arg0[13]);
    t = sp48;
    if (t) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t);
    }
    t = sp4C;
    if (t) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t);
    }
}
}
