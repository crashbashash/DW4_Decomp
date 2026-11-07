int FUN_00171690();
extern int DAT_005608d4[4];
typedef struct { float x; float y; float z; float w; } V4;
typedef struct { char pad[48]; V4 v; char pad2[44]; volatile int flags; } E;
typedef struct { char pad[16]; char *f10; } Tab;
typedef struct { char pad[1336]; Tab *f538; } A;
void Gap__Gfx__igPsx2VisualContext__vfunc_86(A *arg0, int arg1, V4 *arg2) {
    Tab *t;
    E *e;
    int same;
    int old;
    int nw;
    t = arg0->f538;
    e = (E *)(t->f10 + arg1 * 160);
    if (e != 0) {
        same = 1;
        if (e->v.x != arg2->x) { same = 0; }
        if (same != 0) {
            same = 1;
            if (e->v.y != arg2->y) { same = 0; }
        }
        if (same != 0) {
            same = 1;
            if (e->v.z != arg2->z) { same = 0; }
        }
        if (same != 0) {
            same = 1;
            if (e->v.w != arg2->w) { same = 0; }
        }
        if (same != 0) {
            DAT_005608d4[0] += 1;
        }
        e->v.x = arg2->x;
        e->v.y = arg2->y;
        e->v.z = arg2->z;
        e->v.w = arg2->w;
        old = e->flags;
        if (arg2->x != 0.0f || arg2->y != 0.0f || arg2->z != 0.0f) {
            e->flags = e->flags | 1;
        } else {
            e->flags = old & ~1;
        }
        nw = e->flags;
        if (old != nw) {
            e->flags = nw | 8;
        }
        FUN_00171690(arg0, e);
    }
}
