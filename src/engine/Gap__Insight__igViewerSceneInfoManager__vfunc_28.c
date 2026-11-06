typedef struct Obj { int w0; int references; } Obj;
typedef struct List { int pad0[2]; int count; int pad1; Obj **data; } List;
typedef struct Hold { char pad[28]; List *l28; } Hold;
typedef struct X { char pad[12]; Hold *f12; } X;
typedef struct Y { char pad[220]; List *f220; long long f224; long long f232; } Y;
typedef struct Q { int a; int b; int c; int d; } Q;
typedef struct A { char pad[20]; Y *f20; int f24; char pad2[152]; List *f180; } A;
int FUN_001c5eb0(Obj **, Hold *, int);
int FUN_004578c0(Y *, Q *);
int FUN_00460330(int);
int igObject_Destroy(Obj *);
extern int DAT_0058c9f0[4];
extern int DAT_0058cae8[4];
extern int DAT_0058caf0[4];
extern int DAT_0058caf8[4];
#define CLEAR(src) { \
    List *l = (src); \
    int n = l->count; \
    int i; \
    int m; \
    int j; \
    Obj *o; \
    for (i = 0; i < n; i++) { \
        o = l->data[i]; \
        if (o != 0) { \
            o->references = o->references - 1; \
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) igObject_Destroy(o); \
        } \
    } \
    m = l->count; \
    for (j = 0; j < m; j++) { \
        l->data[j] = 0; \
    } \
    l->count = 0; }
void Gap__Insight__igViewerSceneInfoManager__vfunc_28(A *arg0) {
    Hold *s2;
    int s0;
    Obj *volatile spAC;
    Obj *t;
    Q q1, q2, q3, q4;
    s2 = (Hold *)((X *)arg0->f20)->f12;
    s0 = (s2->l28 != 0 ? s2->l28->count : 0) - 1;
    while (s0 >= 0) {
        FUN_001c5eb0((Obj **)&spAC, s2, s0);
        t = spAC;
        if (t != 0) {
            t->references = t->references - 1;
            t = spAC;
            if (((unsigned long long)((long long)t->references << 0x29) >> 0x29) == 0) igObject_Destroy(t);
        }
        s0 -= 1;
    }
    q1.b = 0;
    q1.a = 2;
    q1.c = DAT_0058c9f0[0];
    FUN_004578c0(arg0->f20, &q1);
    FUN_00460330(arg0->f24);
    CLEAR(arg0->f20->f220)
    q2.a = 2;
    q2.b = 0;
    q2.c = DAT_0058cae8[0];
    FUN_004578c0(arg0->f20, &q2);
    arg0->f20->f224 = 0;
    q3.a = 2;
    q3.b = 0;
    q3.c = DAT_0058caf0[0];
    FUN_004578c0(arg0->f20, &q3);
    arg0->f20->f232 = 0;
    q4.a = 2;
    q4.b = 0;
    q4.c = DAT_0058caf8[0];
    FUN_004578c0(arg0->f20, &q4);
    CLEAR(arg0->f180)
}
