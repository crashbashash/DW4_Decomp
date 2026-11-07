int Gap__Core__igObject__vfunc_11();
int List_Resize();
int ObjectList_AppendRetained();
int igObject_Destroy();
int igObject_GetAllocator();
int FUN_00455ad0();
struct ObserverRefView { int w0; int rc; };
struct ObserverIntListView { int w0; int w4; volatile int cnt; int cap; int *data; };
struct ObserverEventView { int w0; int rc; int w8; int a; struct ObserverIntListView *list; };
struct ObserverModelView { char pad[40]; struct ObserverRefView *ref; int flags; int fn; };
struct MousePosObserverView { char pad[16]; struct ObserverModelView *m; int f20; };
struct ObserverEventView *FUN_0019e680();
void Gap__Gui__igMousePosObserver__vfunc_13(struct MousePosObserverView *arg0) {
    struct ObserverEventView * volatile sp4C;
    struct ObserverEventView *q;
    struct ObserverEventView *r;
    struct ObserverIntListView *l;
    int n;
    struct ObserverModelView *m;
    struct ObserverRefView *old;
    struct ObserverEventView *t;
    struct ObserverModelView *m2;
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
    r = sp4C;
    m = arg0->m;
    if (r != 0) {
        r->rc = r->rc + 1;
    }
    old = m->ref;
    if (old != 0) {
        old->rc = old->rc - 1;
        if ((old->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    m->ref = (struct ObserverRefView *)r;
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
