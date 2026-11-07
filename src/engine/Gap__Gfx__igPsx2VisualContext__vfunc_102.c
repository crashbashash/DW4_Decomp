typedef struct P { char pad16[16]; float v[4]; } P;
typedef struct T { char pad1344[1344]; P *f1344; } T;
int FUN_00172330();
extern int DAT_005608f8[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_102(T *arg0, float *arg1) {
    P *p;
    int eq;
    float *cur;

    p = arg0->f1344;
    eq = 1;
    cur = p->v;
    if (cur[0] != arg1[0]) {
        eq = 0;
    }
    if (eq != 0) {
        eq = 1;
        if (cur[1] != arg1[1]) {
            eq = 0;
        }
    }
    if (eq != 0) {
        eq = 1;
        if (cur[2] != arg1[2]) {
            eq = 0;
        }
    }
    if (eq != 0) {
        eq = 1;
        if (cur[3] != arg1[3]) {
            eq = 0;
        }
    }
    if (eq != 0) {
        DAT_005608f8[0] += 1;
    }
    p = arg0->f1344;
    p->v[0] = arg1[0];
    p->v[1] = arg1[1];
    p->v[2] = arg1[2];
    p->v[3] = arg1[3];
    FUN_00172330(arg0, arg0->f1344, cur);
}
