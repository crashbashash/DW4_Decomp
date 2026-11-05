struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct O { char pad[8]; struct Ref *f8; };
struct Ref *FUN_00187e10();
int FUN_0023b140();
int igObject_Destroy();
int FUN_0023b270(struct Ref **arg0, struct O *arg1, int arg2) {
    volatile struct { char c; struct Ref *p; } sp;
    struct Ref *s0;
    struct Ref *p;
    sp.c = 0;
    sp.p = FUN_00187e10(0);
    s0 = sp.p;
    if (s0 != 0) {
        s0->u.w = s0->u.w + 1;
    }
    p = arg1->f8;
    if (p != 0) {
        p->u.w = p->u.w - 1;
        if (p->u.b.cnt == 0) igObject_Destroy(p);
    }
    arg1->f8 = s0;
    FUN_0023b140(arg1, arg2);
    p = arg1->f8;
    if (p != 0) {
        p->u.w = p->u.w - 1;
        if (p->u.b.cnt == 0) igObject_Destroy(p);
    }
    arg1->f8 = 0;
    *arg0 = sp.p;
    p = *arg0;
    if (p != 0) {
        p->u.w = p->u.w + 1;
    }
    p = sp.p;
    if (p != 0) {
        p->u.w = p->u.w - 1;
        if (p->u.b.cnt == 0) igObject_Destroy(p);
    }
    return 0;
}
