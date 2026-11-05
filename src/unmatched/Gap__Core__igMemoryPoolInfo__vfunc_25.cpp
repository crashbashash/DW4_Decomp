extern "C" {
int FUN_00306360(int, char *, int);
int FUN_00306770(int, int, int *, void *, void *, int);
void igObject_Destroy(void *);
extern char * DAT_004c2228[4];
extern char * DAT_004c22f0[4];
extern int DAT_004e0858[4];
extern int DAT_004f7910[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int D_004fb410[4];
}
struct R { int v; R() {} };
union Ref { int w; struct { unsigned cnt:23; unsigned f:9; } b; };
struct Rc { int vt; Ref u; int f8; };
struct G { char p[56]; int f56; };
extern G * DAT_00586dc8[4];
class P { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual R v24(int, int); int f4; int *f8;};

extern "C" int Gap__Core__igMemoryPoolInfo__vfunc_25(int *arg0, P *arg1, int arg2, char *arg3);
extern "C" int Gap__Core__igMemoryPoolInfo__vfunc_25(int *arg0, P *arg1, int arg2, char *arg3) {
    Rc *volatile sp5C;
    int *pp;
    int a;
    int s0;
    char *a3;
    int v0;
    int *a2;
    Rc *q;

    a3 = arg3;
    sp5C = 0;
    s0 = -1;
    if (arg2 == 0) {
        arg2 = DAT_00586dc8[0]->f56;
    }
    if (arg2 == 0) {
        *arg0 = DAT_004fb418[0];
q = sp5C;
        if (q != 0) {
            q->u.w = q->u.w - 1;
            if (q->u.b.cnt == 0) {
                igObject_Destroy(q);
            }
        }
        return 0;
    }
    if (a3 == 0 || *a3 == 0) {
        v0 = FUN_00306360(arg2, DAT_004c2228[0], 0);
        if (v0 == -1) {
            *arg0 = DAT_004fb418[0];
q = sp5C;
            if (q != 0) {
                q->u.w = q->u.w - 1;
                if (q->u.b.cnt == 0) {
                    igObject_Destroy(q);
                }
            }
            return 0;
        }
        a2 = arg1->f8;
        a2 = a2 ? a2 : &DAT_004e0858[0];
        if (FUN_00306770(arg2, v0, a2, (void *)&sp5C, &DAT_004f7910[0], 0) == 0) {
            *arg0 = DAT_004fb418[0];
q = sp5C;
            if (q != 0) {
                q->u.w = q->u.w - 1;
                if (q->u.b.cnt == 0) {
                    igObject_Destroy(q);
                }
            }
            return 0;
        }
        q = sp5C;
        a3 = (char *)q->f8;
        a3 = (a3 == 0) ? DAT_004c22f0[0] : a3;
    }
    if (a3 != 0 && *a3 != 0) {
        s0 = FUN_00306360(arg2, a3, 0);
        if (s0 == -1) {
            *arg0 = DAT_004fb418[0];
q = sp5C;
            if (q != 0) {
                q->u.w = q->u.w - 1;
                if (q->u.b.cnt == 0) {
                    igObject_Destroy(q);
                }
            }
            return 0;
        }
    }
    R sp58 = arg1->v24(arg2, s0);
    pp = (int *)((int)&sp58.v + 0);
    a = D_004fb410[0];
    if (*pp == DAT_004fb410[0]) {
        *arg0 = a;
q = sp5C;
        if (q != 0) {
            q->u.w = q->u.w - 1;
            if (q->u.b.cnt == 0) {
                igObject_Destroy(q);
            }
        }
        return 0;
    }
    *arg0 = DAT_004fb418[0];
q = sp5C;
    if (q != 0) {
        q->u.w = q->u.w - 1;
        if (q->u.b.cnt == 0) {
            igObject_Destroy(q);
        }
    }
    return 0;
}
