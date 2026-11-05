struct Obj { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; int f8; };
struct E { int p0, p4, p8; Obj *f12; int f16; };
struct P { int pad[5]; int f20; int pad2[1]; int f28; };
extern "C" {
int FUN_001c6520(P *, int);
int FUN_001c66c0(P *, int);
int FUN_001c6fa0(void *, P *);
int FUN_001ccd10(P *, int);
int FUN_001cd9f0(void *, P *, int);
int FUN_001cdbb0(void *, P *, int);
int FUN_002da780(Obj *);
int FUN_002da850(Obj *, int);
E *FUN_00307630(int, int);
int FUN_00307650(int);
int FUN_0030ba90(int, void *);
void StringChunk_ReleaseHeader(int, int *);
void igObject_Destroy(void *);
extern int DAT_004c22f0[4];
extern int DAT_004e46e0[4];
void FUN_001cce60(P *arg0) {
    int *sp4C;
    Obj *volatile sp48;
    Obj *sp44;
    Obj *sp40;
    Obj *t;
    Obj *u;
    int s0;
    int v;
    E *e;
    int a2;
    if (arg0->f20 != 0) {
        FUN_001c6520(arg0, 0);
        FUN_001c66c0(arg0, 0);
        FUN_001c6fa0(&sp4C, arg0);
        if (sp4C != 0) {
            sp48 = 0;
            t = sp48;
            if (t != 0) t->u.w = t->u.w + 1;
            FUN_001cd9f0(&sp44, arg0, (int)sp4C);
            u = sp44;
            if (u != 0) u->u.w = u->u.w + 1;
            t = sp48;
            if (t != 0) {
                t->u.w = t->u.w - 1;
                if (t->u.b.cnt == 0) igObject_Destroy(t);
            }
            sp48 = u;
            if (sp44 != 0) {
                sp44->u.w = sp44->u.w - 1;
                if (sp44->u.b.cnt == 0) igObject_Destroy(sp44);
            }
            t = sp48;
            if (t != 0) {
                v = FUN_002da780(t);
                FUN_001ccd10(arg0, v);
                FUN_002da850(sp48, v);
            }
            t = sp48;
            if (t != 0) {
                t->u.w = t->u.w - 1;
                if (t->u.b.cnt == 0) igObject_Destroy(t);
            }
        }
        for (s0 = 0; s0 < FUN_00307650(arg0->f28); s0++) {
            e = FUN_00307630(arg0->f28, s0);
            if (e != 0 && e->f16 != 0 && e->f12 != 0 && FUN_0030ba90(e->f16, &DAT_004e46e0[0]) != 0) {
                if (e->f12->f8 == 0) a2 = DAT_004c22f0[0]; else a2 = e->f12->f8;
                FUN_001cdbb0(&sp40, arg0, a2);
                if (sp40 != 0) {
                    sp40->u.w = sp40->u.w - 1;
                    if (sp40->u.b.cnt == 0) igObject_Destroy(sp40);
                }
            }
        }
        if (sp4C != 0) {
            int *h = sp4C - 2;
            int c = sp4C[-1] - 1;
            sp4C[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
    }
}
}
