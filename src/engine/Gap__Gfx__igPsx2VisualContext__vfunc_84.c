int FUN_00171690();
extern int DAT_005609c8[4];
typedef struct E { char p0[16]; float v0, v1, v2, v3; char p1[76]; int f108; char p2[48]; } E;
typedef struct T { char p0[16]; E *f16; } T;
typedef struct O { char p0[1336]; T *f1336; } O;
void Gap__Gfx__igPsx2VisualContext__vfunc_84(O *arg0, int arg1, float *arg2) {
    T *t;
    E *e;
    int same;
    int old;
    t = arg0->f1336;
    e = (E *)((char *)t->f16 + arg1 * 160);
    if (e != 0) {
        same = 1;
        if (e->v0 != arg2[0]) same = 0;
        if (same) {
            same = 1;
            if (e->v1 != arg2[1]) same = 0;
        }
        if (same) {
            same = 1;
            if (e->v2 != arg2[2]) same = 0;
        }
        if (same) {
            same = 1;
            if (e->v3 != arg2[3]) same = 0;
        }
        if (same) {
            DAT_005609c8[0] = DAT_005609c8[0] + 1;
        }
        e->v0 = arg2[0];
        e->v1 = arg2[1];
        e->v2 = arg2[2];
        e->v3 = arg2[3];
        old = e->f108;
        if (arg2[0] != 0.0f || arg2[1] != 0.0f || arg2[2] != 0.0f) {
            e->f108 = e->f108 | 0x10;
        } else {
            e->f108 = old & ~0x10;
        }
        if (old != e->f108) {
            e->f108 = e->f108 | 8;
        }
        FUN_00171690(arg0, e);
    }
}
