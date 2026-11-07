struct SharedObjectView { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct ObjectSlotOwner { char pad[8]; struct SharedObjectView *f8; };
struct SharedObjectView *FUN_00187e10();
int FUN_0023b140();
int igObject_Destroy();
int FUN_0023b270(struct SharedObjectView **arg0, struct ObjectSlotOwner *arg1, int arg2) {
    struct SharedObjectView * volatile spp;
    volatile char spc[4];
    struct SharedObjectView *s0;
    struct SharedObjectView *p;
    spc[0] = 0;
    spp = FUN_00187e10(0);
    s0 = spp;
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
    *arg0 = spp;
    p = *arg0;
    if (p != 0) {
        p->u.w = p->u.w + 1;
    }
    p = spp;
    if (p != 0) {
        p->u.w = p->u.w - 1;
        if (p->u.b.cnt == 0) igObject_Destroy(p);
    }
    return 0;
}
