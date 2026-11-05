extern "C" {
void *FUN_002ba650(...);
void igObject_Destroy(void *);
int igObject_GetAllocator(void *);
extern int DAT_004fb410[4];
}
struct R { int v; R() {} R(int x) { v = x; } };
struct RO { int vt; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
class Rc {
public:
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
    virtual R v92();
    virtual R v96();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual R v132(int);
};
struct OB { char pad[116]; Rc *f116; };
struct Rel { static inline void go(Rc *o) { RO *t = (RO *)o; if (t != 0) { t->u.w = t->u.w - 1; if (t->u.b.cnt == 0) igObject_Destroy(t); } } };
extern "C" {
R Gap__Core__igMallocMemoryPool__vfunc_34(OB *arg1, unsigned char arg2) {
    Rc * volatile sp5C;
    Rc * volatile sp58;
    R sp54;
    R sp50;
    R sp4C;
    if (arg2 == 0) {
        sp5C = arg1->f116;
        { Rc *t0 = sp5C; if (t0 != 0) { RO *t = (RO *)t0; t->u.w = t->u.w + 1; } }
        Rel::go(arg1->f116);
        arg1->f116 = 0;
        Rc *t1 = sp5C;
        if (t1 != 0) {
            sp54 = t1->v132(1);
            sp50 = sp5C->v96();
        }
        Rel::go(arg1->f116);
        arg1->f116 = 0;
        Rel::go(sp5C);
    } else if (arg2 == 1) {
        if (arg1->f116 != 0) return R(DAT_004fb410[0]);
        sp58 = (Rc *)FUN_002ba650(igObject_GetAllocator(arg1));
        sp4C = sp58->v92();
        Rc *s0 = sp58;
        if (s0 != 0) { RO *t = (RO *)s0; t->u.w = t->u.w + 1; }
        Rel::go(arg1->f116);
        arg1->f116 = s0;
        Rel::go(sp58);
    }
    return R(DAT_004fb410[0]);
}
}
