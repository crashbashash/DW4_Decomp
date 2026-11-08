int FUN_00172330(void *, void *);
extern int DAT_00560904[4];
struct VisualContextVec4 { float x, y, z, w; };
struct VisualContextState { char pad[32]; struct VisualContextVec4 v; char pad2[20]; unsigned flags; };
struct Psx2VisualContextView { char pad[1344]; struct VisualContextState *o; };
void Gap__Gfx__igPsx2VisualContext__vfunc_108(struct Psx2VisualContextView *arg0, struct VisualContextVec4 *arg1) {
    struct VisualContextVec4 *p;
    struct VisualContextState *o;
    unsigned old;
    unsigned *fp;
    int same;

    o = arg0->o;
    p = &o->v;
    same = p->x == arg1->x && p->y == arg1->y && p->z == arg1->z && p->w == arg1->w;
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
