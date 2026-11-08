typedef struct VisualColorBlock { char pad16[16]; float v[4]; } VisualColorBlock;
typedef struct VisualContextColorView { char pad1344[1344]; VisualColorBlock *f1344; } VisualContextColorView;
int FUN_00172330();
extern int DAT_005608f8[4];
static inline int colorEqual(const float *a, const float *b) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}
void Gap__Gfx__igPsx2VisualContext__vfunc_102(VisualContextColorView *arg0, float *arg1) {
    float *cur = arg0->f1344->v;
    VisualColorBlock *p;
    if (colorEqual(cur, arg1)) {
        DAT_005608f8[0] += 1;
    }
    p = arg0->f1344;
    p->v[0] = arg1[0];
    p->v[1] = arg1[1];
    p->v[2] = arg1[2];
    p->v[3] = arg1[3];
    FUN_00172330(arg0, arg0->f1344, cur);
}
