int FUN_00172330(void *, void *);
extern int DAT_00560904[4];
struct V { float x, y, z, w; };
struct O { char pad[32]; struct V v; char pad2[20]; unsigned flags; };
struct A { char pad[1344]; struct O *o; };
void FUN_00171b10(struct A *arg0, struct V *arg1) {
    struct V *p;
    struct O *o;
    unsigned old;
    unsigned *fp;
    int same;

    o = arg0->o;
    p = &o->v;
    same = 1;
    if (p->x != arg1->x) same = 0;
    if (same) { same = 1; if (p->y != arg1->y) same = 0; }
    if (same) { same = 1; if (p->z != arg1->z) same = 0; }
    if (same) { same = 1; if (p->w != arg1->w) same = 0; }
    if (same) {
        DAT_00560904[0] += 1;
    }
    o = arg0->o;
    o->v.x = arg1->x;
    o->v.y = arg1->y;
    o->v.z = arg1->z;
    o->v.w = arg1->w;
    o = arg0->o;
    fp = &o->flags;
    old = *fp;
    if (arg1->x != 0.0f || arg1->y != 0.0f || arg1->z != 0.0f) {
        *fp = *fp | 1;
    } else {
        *fp = old & ~1;
    }
    o = arg0->o;
    fp = &o->flags;
    if (old != *fp) {
        *fp = *fp | 2;
    }
    FUN_00172330(arg0, arg0->o);
}
