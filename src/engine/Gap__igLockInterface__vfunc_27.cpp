typedef struct Rc { int w0; int refs; } Rc;
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int); int w4; };
extern "C" {
Rc *FUN_002279d0(int);
int igLockBase_GetMetaObject();
int FUN_0022a8d0(Rc *, int);
O *FUN_0022a950(Rc *);
int FUN_0022a9d0(Rc *);
int FUN_002fd610(O **, O *);
int FUN_002295b0(int, O *);
int igObject_Destroy(void *);
int Gap__igLockInterface__vfunc_27(int arg0, int arg1);
int Gap__igLockInterface__vfunc_27(int arg0, int arg1) {
    Rc *volatile sp4C;
    O *volatile sp48;
    O *sp44;
    volatile char sp40[4];
    O *v;
    O *a1;
    Rc *t;
    O *u;
    sp40[0] = 0;
    sp4C = FUN_002279d0(0);
    FUN_0022a8d0(sp4C, igLockBase_GetMetaObject());
    for (;;) {
        v = FUN_0022a950(sp4C);
        if (((v != 0) ^ 1) != 0) break;
        FUN_0022a9d0(sp4C);
        FUN_002fd610((O **)&sp44, v);
        sp48 = sp44;
        u = sp48;
        if (u != 0) u->w4 = u->w4 + 1;
        u = sp44;
        if (u != 0) {
            u->w4 = u->w4 - 1;
            u = sp44;
            if (((unsigned long long)(long long)u->w4 & 0x7fffffULL) == 0) igObject_Destroy(u);
        }
        a1 = sp48;
        if (a1 == 0) {
            if (a1 != 0) {
                a1->w4 = a1->w4 - 1;
                if (((unsigned long long)(long long)a1->w4 & 0x7fffffULL) == 0) igObject_Destroy(a1);
            }
            continue;
        }
        FUN_002295b0(arg0, a1);
        if (sp48->vX(arg1) != 0) {
            u = sp48;
            if (u != 0) {
                u->w4 = u->w4 - 1;
                if (((unsigned long long)(long long)u->w4 & 0x7fffffULL) == 0) igObject_Destroy(u);
            }
            t = sp4C;
            if (t != 0) {
                t->refs = t->refs - 1;
                if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t);
            }
            return 1;
        }
        u = sp48;
        if (u != 0) {
            u->w4 = u->w4 - 1;
            if (((unsigned long long)(long long)u->w4 & 0x7fffffULL) == 0) igObject_Destroy(u);
        }
    }
    t = sp4C;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t);
    }
    return 0;
}
}
