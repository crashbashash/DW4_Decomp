int Gap__Core__igObject__vfunc_11();
int List_Resize();
int ObjectList_AppendRetained();
int igObject_Destroy();
int igObject_GetAllocator();
int FUN_00455ad0();
struct R { int w0; int rc; };
struct L { int w0; int w4; volatile int cnt; int cap; int *data; };
struct X { int w0; int rc; int w8; int a; struct L *list; };
struct M { char pad[40]; struct R *ref; int flags; int fn; };
struct O { char pad[16]; struct M *m; int f20; };
struct X *FUN_0019e680();
void FUN_00455c30(struct O *arg0) {
    struct X * volatile sp4C;
    struct X *q;
    struct L *l;
    int n;
    struct M *m;
    struct R *old;
    struct X *t;
    struct M *m2;
    Gap__Core__igObject__vfunc_11();
    sp4C = FUN_0019e680(igObject_GetAllocator(arg0));
    q = sp4C;
    ObjectList_AppendRetained(q->a, arg0->f20);
    l = q->list;
    n = l->cnt;
    if (n < l->cap) {
        l->cnt = l->cnt + 1;
    } else {
        List_Resize(l, n + 1, 4);
    }
    l->data[n] = 2;
    q = sp4C;
    m = arg0->m;
    if (q != 0) {
        q->rc = q->rc + 1;
    }
    old = m->ref;
    if (old != 0) {
        old->rc = old->rc - 1;
        if ((old->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    m->ref = (struct R *)q;
    arg0->m->flags = 0;
    m2 = arg0->m;
    m2->flags = m2->flags | 4;
    arg0->m->fn = (int)&FUN_00455ad0;
    t = sp4C;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
}
