typedef struct V4 { float x, y, z, w; } V4;
typedef struct Sub { V4 v; char pad[52]; unsigned flags; } Sub;
typedef struct Obj { char pad[1344]; struct Sub *s; } Obj;
extern int DAT_005608fc[4];
void FUN_00172330(Obj *o, Sub *s);
void Gap__Gfx__igPsx2VisualContext__vfunc_106(Obj *o, V4 *n) {
    Sub *s;
    unsigned old, *f;
    int eq;
    s = o->s;
    eq = (s->v.x == n->x);
    if (eq) eq = (s->v.y == n->y);
    if (eq) eq = (s->v.z == n->z);
    if (eq) eq = (s->v.w == n->w);
    if (eq) DAT_005608fc[0]++;
    s = o->s;
    s->v.x = n->x; s->v.y = n->y; s->v.z = n->z; s->v.w = n->w;
    s = o->s;
    f = &s->flags;
    old = s->flags;
    if (n->x != 0.0f || n->y != 0.0f || n->z != 0.0f) *f |= 4;
    else *f = old & ~4u;
    s = o->s;
    f = &s->flags;
    if (old != s->flags) *f = s->flags | 2;
    FUN_00172330(o, o->s);
}
